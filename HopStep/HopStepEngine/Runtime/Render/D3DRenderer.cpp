#include "D3DRenderer.h"
#include "D3DUtils.h"
#include "..\..\Core\Misc\Paths.h"
#include "..\..\Core\Misc\GenericMemory.h"	
#include "..\..\Core\GenericPlatform\GenericWindow.h"
#include "..\..\Core\Windows\WindowsWindow.h"
#include "Runtime\Engine\AssetImporter.h"
#include "Runtime\Engine\GameView.h"

namespace HopStep
{
	HD3DRenderer::HD3DRenderer(TSharedPtr<HGenericWindow> AppWindowPtr, TSharedPtr<class HGameView> InView)
		: AppWindow(AppWindowPtr)
		, ViewInfo(InView)
		, AspectRatio(static_cast<float>(AppWindowPtr->GetClientWidth()) / static_cast<float>(AppWindowPtr->GetClientHeight()))
		, Viewport(CD3DX12_VIEWPORT(0.0f, 0.0f, static_cast<float>(AppWindowPtr->GetClientWidth()), static_cast<float>(AppWindowPtr->GetClientHeight())))
		, ScissorRect(CD3DX12_RECT(0, 0, AppWindowPtr->GetClientWidth(), AppWindowPtr->GetClientHeight()))
	{
	}

	HD3DRenderer::~HD3DRenderer()
	{
	}

	bool HD3DRenderer::OnInit()
	{
#if _DEBUG
		// Enable debug layer
		{
			ComPtr<ID3D12Debug> DebugController;
			ThrowIfFailed(D3D12GetDebugInterface(IID_PPV_ARGS(&DebugController)));
			DebugController->EnableDebugLayer();
		}
#endif

		ThrowIfFailed(CreateDXGIFactory1(IID_PPV_ARGS(&DXGIFactory)));

		HRESULT HardwareResult = D3D12CreateDevice(
			nullptr, // Default adapter
			D3D_FEATURE_LEVEL_11_0,
			IID_PPV_ARGS(&Device)
		);

		// WARP Device if failed
		if (FAILED(HardwareResult))
		{
			ComPtr<IDXGIAdapter> WarpAdapter;
			ThrowIfFailed(DXGIFactory->EnumWarpAdapter(IID_PPV_ARGS(&WarpAdapter)));
			ThrowIfFailed(D3D12CreateDevice(WarpAdapter.Get(), D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&Device)));
		}

		ThrowIfFailed(Device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&Fence)));
		
		// Get descriptor size
		{
			RenderTargetViewDescriptorSize = Device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
			DepthStencilViewDescripotSize = Device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);
			CbvSrvUavDescriptorSize = Device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
		}

		DebugLogAdapters();

		// Create Command Objects
		{
			D3D12_COMMAND_QUEUE_DESC CommandQueueDesc = 
			{
				.Type = D3D12_COMMAND_LIST_TYPE_DIRECT,
				.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE
			};
			ThrowIfFailed(Device->CreateCommandQueue(&CommandQueueDesc, IID_PPV_ARGS(&CommandQueue)));
			ThrowIfFailed(Device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(CommandAllocator.GetAddressOf())));
			ThrowIfFailed(Device->CreateCommandList(
				0,
				D3D12_COMMAND_LIST_TYPE_DIRECT,
				CommandAllocator.Get(), // Associated allocator
				nullptr, // Initial pipeline state object
				IID_PPV_ARGS(CommandList.GetAddressOf()))
			);

			// Close 상태로 시작해준다.
			// 매 프레임 CommandList::Reset()을 호출한 뒤 시작해줄 것인데, Reset()은 CommandList가 Close 상태이길 필요로하기 때문.
			CommandList->Close();
		}
		
		// Create swap chain
		{
			SwapChain.Reset();

			DXGI_MODE_DESC BufferDesc =
			{
				.Width = AppWindow->GetClientWidth(),
				.Height = AppWindow->GetClientHeight(),
				.RefreshRate = DXGI_RATIONAL( 60, 1 ),
				.Format = BackBufferFormat,
				.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED,
				.Scaling = DXGI_MODE_SCALING_UNSPECIFIED
			};

			DXGI_SWAP_CHAIN_DESC Desc =
			{
				.BufferDesc = BufferDesc,
				.SampleDesc = DXGI_SAMPLE_DESC(1, 0),
				.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT,
				.BufferCount = SwapChainBufferCount,
				.OutputWindow = HWindowsWindow::GetWindowHandle(),
				.Windowed = true,
				.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD,
				.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH
			};

			ThrowIfFailed(DXGIFactory->CreateSwapChain(CommandQueue.Get(), &Desc, SwapChain.GetAddressOf()));
		}

		// Create descriptor heaps
		{
			D3D12_DESCRIPTOR_HEAP_DESC RenderTargetViewHeapDesc = 
			{
				.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV,
				.NumDescriptors = SwapChainBufferCount,
				.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE,
				.NodeMask = 0
			};
			ThrowIfFailed(Device->CreateDescriptorHeap(&RenderTargetViewHeapDesc, IID_PPV_ARGS(&RenderTargetViewHeap)));

			D3D12_DESCRIPTOR_HEAP_DESC DepthStencilViewHeapDesc = 
			{
				.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV,
				.NumDescriptors = SwapChainBufferCount,
				.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE,
				.NodeMask = 0
			};
			ThrowIfFailed(Device->CreateDescriptorHeap(&DepthStencilViewHeapDesc, IID_PPV_ARGS(&DepthStencilViewHeap)));
		}

		// Inherited specific app layer
		// Command가 들어가기 전에 Reset 해주자.
		ThrowIfFailed(CommandList->Reset(CommandAllocator.Get(), nullptr));

		// Build Constant buffer view heap && Constant buffer
		{
			D3D12_DESCRIPTOR_HEAP_DESC ConstantBufferViewHeapDesc = 
			{
				.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV,
				.NumDescriptors = 1,
				.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE,
				.NodeMask = 0
			};
			ThrowIfFailed(Device->CreateDescriptorHeap(&ConstantBufferViewHeapDesc, IID_PPV_ARGS(&ConstantBufferViewHeap)));

			ObjectConstantBuffer = std::make_unique<TUploadBuffer<HObjectConstantBuffer>>(Device.Get(), 1, true);

			uint32 ObjectCBByteSize = ObjectConstantBuffer->GetElementByteSize();
			D3D12_GPU_VIRTUAL_ADDRESS VAddress = ObjectConstantBuffer->Resource()->GetGPUVirtualAddress();

			D3D12_CONSTANT_BUFFER_VIEW_DESC BufferViewDesc = 
			{
				.BufferLocation = VAddress,
				.SizeInBytes = ObjectCBByteSize
			};

			Device->CreateConstantBufferView(&BufferViewDesc, ConstantBufferViewHeap->GetCPUDescriptorHandleForHeapStart());
		}

		// Build Root signature
		// 루트 시그니쳐는 Shader에 바인딩 될 리소스들을 정의해주는 역할을 한다. (CBV나 Texture나 Sampler나...)
		// 왜 루트 시그니쳐냐면, Shader program을 function이라고 생각하고, 인풋 리소스를 파라메터라고 생각하면, 이 루트 시그니쳐가 그 쉐이더의 함수 시그니쳐를 정의하기 때문에.
		{
			// Root parameter는 Root descriptor나 Root constants의 table이라고 생각하면 된다.
			CD3DX12_ROOT_PARAMETER RootParamterSlots[1] = { CD3DX12_ROOT_PARAMETER() };

			// CBV Descriptor table을 만들자
			CD3DX12_DESCRIPTOR_RANGE CBVDescriptorTable;
			CBVDescriptorTable.Init(D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 1, 0);
			RootParamterSlots[0].InitAsDescriptorTable(1, &CBVDescriptorTable);

			// 루트 시그니쳐는 Root Parameter의 리스트다.
			CD3DX12_ROOT_SIGNATURE_DESC RootSigDesc = CD3DX12_ROOT_SIGNATURE_DESC(1, RootParamterSlots, 0, nullptr, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

			// 위에서 만든 Desc로 루트 시그니쳐를 만들 것이다. 우리의 시그니쳐는 단일 CBV 디스크립터 하나 만을 가리키고 있다.
			ComPtr<ID3DBlob> SerializedRootSig = nullptr;
			ComPtr<ID3DBlob> ErrorMsg = nullptr;

			HRESULT Result = D3D12SerializeRootSignature(&RootSigDesc, D3D_ROOT_SIGNATURE_VERSION_1, SerializedRootSig.GetAddressOf(), ErrorMsg.GetAddressOf());

			if (ErrorMsg != nullptr)
			{
				::OutputDebugStringA((char*)ErrorMsg->GetBufferPointer());
			}
			ThrowIfFailed(Result);
			ThrowIfFailed(Device->CreateRootSignature(0, SerializedRootSig->GetBufferPointer(), SerializedRootSig->GetBufferSize(), IID_PPV_ARGS(&RootSignature)));
		}

		// Compile shader and define input layout
		{
			HString ShaderPath = HPaths::ShaderPath().append(TEXT("shaders.hlsl"));
			VertexShaderByteCode = HRenderPipelineUtils::CompileShaderFromFile(ShaderPath.c_str(), "VSMain", "vs_5_0");
			PixelShaderByteCode = HRenderPipelineUtils::CompileShaderFromFile(ShaderPath.c_str(), "PSMain", "ps_5_0");

			InputLayout =
			{
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
				{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
			};
		}

		BuildMeshResource();

		return true;
	}

	void HD3DRenderer::OnUpdate()
	{
	}

	void HD3DRenderer::OnRender()
	{
	}

	void HD3DRenderer::OnDestroy()
	{
	}

	void HD3DRenderer::DebugLogAdapters() const
	{
#if _DEBUG
		uint32 Index = 0u;
		IDXGIAdapter* AdapterPtr = nullptr;

		TArray<IDXGIAdapter*> AdapterList;

		while (DXGIFactory->EnumAdapters(Index++, &AdapterPtr) != DXGI_ERROR_NOT_FOUND)
		{
			DXGI_ADAPTER_DESC Desc;
			AdapterPtr->GetDesc(&Desc);

			HString DescText = TEXT("*** Adapter: ");
			DescText += Desc.Description;
			DescText += TEXT("\n");

			OutputDebugString(DescText.c_str());
			AdapterList.push_back(AdapterPtr);
		}

		for (Size_t I = Size_t{ 0u }; I < AdapterList.size(); ++I)
		{
			IDXGIAdapter* Adapter = AdapterList[I];
			Adapter->Release();
			Adapter = nullptr;
		}
#endif
	}

	void HD3DRenderer::BuildMeshResource()
	{
		TArray<HVertex> Vertices =
		{
			HVertex({ XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT4(HColors::White) }),
			HVertex({ XMFLOAT3(-1.0f, +1.0f, -1.0f), XMFLOAT4(HColors::Black) }),
			HVertex({ XMFLOAT3(+1.0f, +1.0f, -1.0f), XMFLOAT4(HColors::Red) }),
			HVertex({ XMFLOAT3(+1.0f, -1.0f, -1.0f), XMFLOAT4(HColors::Green) }),
			HVertex({ XMFLOAT3(-1.0f, -1.0f, +1.0f), XMFLOAT4(HColors::Blue) }),
			HVertex({ XMFLOAT3(-1.0f, +1.0f, +1.0f), XMFLOAT4(HColors::Yellow) }),
			HVertex({ XMFLOAT3(+1.0f, +1.0f, +1.0f), XMFLOAT4(HColors::Cyan) }),
			HVertex({ XMFLOAT3(+1.0f, -1.0f, +1.0f), XMFLOAT4(HColors::Magenta) })
		};

		TArray<uint16> Indices =
		{
			// front face
			0, 1, 2,
			0, 2, 3,

			// back face
			4, 6, 5,
			4, 7, 6,

			// left face
			4, 5, 1,
			4, 1, 0,

			// right face
			3, 2, 6,
			3, 6, 7,

			// top face
			1, 5, 6,
			1, 6, 2,

			// bottom face
			4, 0, 3,
			4, 3, 7
		};

		const uint32 VBByteSize = (uint32)Vertices.size() * sizeof(HVertex);
		const uint32 IBByteSize = (uint32)Indices.size() * sizeof(uint16);

		MeshResource = std::make_unique<HMeshResource>();

		ThrowIfFailed(D3DCreateBlob(VBByteSize, &MeshResource->VertexBufferCPU));
		HGenericMemory::MemCpy(MeshResource->VertexBufferCPU->GetBufferPointer(), Vertices.data(), VBByteSize);

		ThrowIfFailed(D3DCreateBlob(IBByteSize, &MeshResource->IndexBufferCPU));
		HGenericMemory::MemCpy(MeshResource->IndexBufferCPU->GetBufferPointer(), Indices.data(), IBByteSize);

		MeshResource->VertexBufferGPU = 
	}
}