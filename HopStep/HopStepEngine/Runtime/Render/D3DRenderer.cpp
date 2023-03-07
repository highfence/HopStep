#include "D3DRenderer.h"
#include "D3DUtils.h"
#include "..\..\Core\Misc\Paths.h"
#include "..\..\Core\Misc\GenericMemory.h"	
#include "..\..\Core\GenericPlatform\GenericWindow.h"
#include "..\..\Core\Windows\WindowsWindow.h"
#include "Runtime\Engine\AssetImporter.h"
#include "Runtime\Engine\GameView.h"
#include <DirectXMath.h>

namespace HopStep
{
	HD3DRenderer::HD3DRenderer(TSharedPtr<HGenericWindow> AppWindowPtr, TSharedPtr<class HGameView> InView)
		: AppWindow(AppWindowPtr)
		, ViewInfo(InView)
		, AspectRatio(static_cast<float>(AppWindowPtr->GetClientWidth()) / static_cast<float>(AppWindowPtr->GetClientHeight()))
		, Viewport(CD3DX12_VIEWPORT(0.0f, 0.0f, static_cast<float>(AppWindowPtr->GetClientWidth()), static_cast<float>(AppWindowPtr->GetClientHeight())))
		, ScissorRect(CD3DX12_RECT(0, 0, AppWindowPtr->GetClientWidth(), AppWindowPtr->GetClientHeight()))
		, Theta(1.5f * ::DirectX::XM_PI)
		, Phi(::DirectX::XM_PIDIV4)
		, Radius(5.0f)
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

			// Close ���·� �������ش�.
			// �� ������ CommandList::Reset()�� ȣ���� �� �������� ���ε�, Reset()�� CommandList�� Close �����̱� �ʿ���ϱ� ����.
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
		// Command�� ���� ���� Reset ������.
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
		// ��Ʈ �ñ״��Ĵ� Shader�� ���ε� �� ���ҽ����� �������ִ� ������ �Ѵ�. (CBV�� Texture�� Sampler��...)
		// �� ��Ʈ �ñ״��ĳĸ�, Shader program�� function�̶�� �����ϰ�, ��ǲ ���ҽ��� �Ķ���Ͷ�� �����ϸ�, �� ��Ʈ �ñ״��İ� �� ���̴��� �Լ� �ñ״��ĸ� �����ϱ� ������.
		{
			// Root parameter�� Root descriptor�� Root constants�� table�̶�� �����ϸ� �ȴ�.
			CD3DX12_ROOT_PARAMETER RootParamterSlots[1] = { CD3DX12_ROOT_PARAMETER() };

			// CBV Descriptor table�� ������
			CD3DX12_DESCRIPTOR_RANGE CBVDescriptorTable;
			CBVDescriptorTable.Init(D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 1, 0);
			RootParamterSlots[0].InitAsDescriptorTable(1, &CBVDescriptorTable);

			// ��Ʈ �ñ״��Ĵ� Root Parameter�� ����Ʈ��.
			CD3DX12_ROOT_SIGNATURE_DESC RootSigDesc = CD3DX12_ROOT_SIGNATURE_DESC(1, RootParamterSlots, 0, nullptr, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

			// ������ ���� Desc�� ��Ʈ �ñ״��ĸ� ���� ���̴�. �츮�� �ñ״��Ĵ� ���� CBV ��ũ���� �ϳ� ���� ����Ű�� �ִ�.
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

		// Build Pipeline state object
		{
			D3D12_GRAPHICS_PIPELINE_STATE_DESC PSODesc = 
			{
				.pRootSignature = RootSignature.Get(),
				.VS = { reinterpret_cast<BYTE*>(VertexShaderByteCode->GetBufferPointer()), VertexShaderByteCode->GetBufferSize() },
				.PS = { reinterpret_cast<BYTE*>(PixelShaderByteCode->GetBufferPointer()), PixelShaderByteCode->GetBufferSize() },
				.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT),
				.SampleMask = UINT_MAX,
				.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT),
				.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT),
				.InputLayout = { InputLayout.data(), (uint32)InputLayout.size() },
				.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE,
				.NumRenderTargets = 1,
				.DSVFormat = DepthStencilFormat,
				.SampleDesc = { 1, 0 },
			};

			PSODesc.RTVFormats[0] = BackBufferFormat;
			ThrowIfFailed(Device->CreateGraphicsPipelineState(&PSODesc, IID_PPV_ARGS(&PSO)));
		}

		ThrowIfFailed(CommandList->Close());
		ID3D12CommandList* CommandLists[] = {CommandList.Get()};
		CommandQueue->ExecuteCommandLists(_countof(CommandLists), CommandLists);

		FlushCommandQueue();

		// Reset render targets
		OnResize();

		return true;
	}

	void HD3DRenderer::OnUpdate()
	{
		using namespace DirectX;

		float x = Radius * sinf(Phi) * cosf(Theta);
		float z = Radius * sinf(Phi) * sinf(Theta);
		float y = Radius * cosf(Phi);

		XMVECTOR Pos = XMVectorSet(x, y, z, 1.0f);
		XMVECTOR Target = XMVectorZero();
		XMVECTOR Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

		XMMATRIX View = XMMatrixLookAtLH(Pos, Target, Up);
		XMStoreFloat4x4(&this->View, View);

		XMMATRIX World = XMLoadFloat4x4(&this->World);
		XMMATRIX Projection = XMLoadFloat4x4(&this->Projection);
		XMMATRIX WorldViewProjection = World * View * Projection;

		HObjectConstantBuffer ObjectConstants;
		XMStoreFloat4x4(&ObjectConstants.WorldViewProj, XMMatrixTranspose(WorldViewProjection));
		ObjectConstantBuffer->CopyData(0, &ObjectConstants);
	}

	void HD3DRenderer::OnRender()
	{
		// Command Allocator�� Reset�� �̿��� Command recording�� ���Ǵ� �޸𸮸� ������ �� �ֵ��� ����.
		// ���õ� ��� Command�� GPU���� ������ ������ ������ Reset�� ������ �� �ִ�.
		ThrowIfFailed(CommandAllocator->Reset());

		// CommandList�� ���������� �޸𸮸� ����. 
		ThrowIfFailed(CommandList->Reset(CommandAllocator.Get(), PSO.Get()));

		// �����Ͷ����� �ܰ迡 ����� �� �ֵ��� ����Ʈ�� ScissorRect�� ����
		CommandList->RSSetViewports(1, &Viewport);
		CommandList->RSSetScissorRects(1, &ScissorRect);

		// �� ���ۿ� �׸� �� �ֵ��� ���� Ÿ�� ���·� ������ش�.
		CD3DX12_RESOURCE_BARRIER PresentToRenderTargetTransitionBarrier = CD3DX12_RESOURCE_BARRIER::Transition(CurrentBackBuffer(), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);
		CommandList->ResourceBarrier(1, &PresentToRenderTargetTransitionBarrier);

		D3D12_CPU_DESCRIPTOR_HANDLE BackBufferViewHandle = CurrentBackBufferView();
		D3D12_CPU_DESCRIPTOR_HANDLE DepthStencilViewHandle = DepthStencilView();

		// �� ���ۿ� ���� ���۸� Ŭ����
		CommandList->ClearRenderTargetView(BackBufferViewHandle, HColors::LightSteelBlue, 0, nullptr);
		CommandList->ClearDepthStencilView(DepthStencilViewHandle, D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL, 1.0f, 0, 0, nullptr);

		// Output Merger (��� ���ձ�) Render Target���� ����
		CommandList->OMSetRenderTargets(1, &BackBufferViewHandle, true, &DepthStencilViewHandle);

		ID3D12DescriptorHeap* DescriptorHeaps[] = { ConstantBufferViewHeap.Get() };
		CommandList->SetDescriptorHeaps(_countof(DescriptorHeaps), DescriptorHeaps);

		CommandList->SetGraphicsRootSignature(RootSignature.Get());

		// Input Assembler setting
		D3D12_VERTEX_BUFFER_VIEW VertexBufferViewHandle = MeshResource->VertexBufferView();
		D3D12_INDEX_BUFFER_VIEW IndexBufferViewHandle = MeshResource->IndexBufferView();
		CommandList->IASetVertexBuffers(0, 1, &VertexBufferViewHandle);
		CommandList->IASetIndexBuffer(&IndexBufferViewHandle);
		CommandList->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		CommandList->SetGraphicsRootDescriptorTable(0, ConstantBufferViewHeap->GetGPUDescriptorHandleForHeapStart());

		// Todo: temp
		CommandList->DrawIndexedInstanced(MeshResource->Submeshes[TEXT("Box")].IndexCount, 1u, 0u, 0u, 0u);

		// �� ���۸� STATE_PRESENT ���·� ����� ǥ�� ��� ���·� ������ش�.
		CD3DX12_RESOURCE_BARRIER RenderTargetToPresentTransitionBarrier = CD3DX12_RESOURCE_BARRIER::Transition(CurrentBackBuffer(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);
		CommandList->ResourceBarrier(1, &RenderTargetToPresentTransitionBarrier);

		// Ŀ�ǵ� ��� ���¸� ������.
		ThrowIfFailed(CommandList->Close());

		// CommandQueue�� Execute�� ��û�Ѵ�.
		ID3D12CommandList* CommandLists[] = { CommandList.Get() };
		CommandQueue->ExecuteCommandLists(_countof(CommandLists), CommandLists);

		// ���۸� �׷��ְ� ����
		ThrowIfFailed(SwapChain->Present(0, 0));
		CurrentBackBufferIndex = (++CurrentBackBufferIndex) % SwapChainBufferCount;

		// Ŀ�ǵ尡 ������ ��ٷ��ش�. �̴� ��ȿ�����̱� ������ �ڵ带 ������ �ϱ� ���� ���⿡ �߰��ص���.
		// ���߿� ������ ����.
		FlushCommandQueue();
	}

	void HD3DRenderer::OnDestroy()
	{
	}

	void HD3DRenderer::OnResize()
	{
		HCheck(Device);
		HCheck(SwapChain);
		HCheck(CommandAllocator);

		FlushCommandQueue();

		ThrowIfFailed(CommandList->Reset(CommandAllocator.Get(), nullptr));

		for (uint32 Idx = 0u; Idx < SwapChainBufferCount; ++Idx)
		{
			SwapChainBuffers[Idx].Reset();
		}

		DepthStencilBuffer.Reset();

		ThrowIfFailed(SwapChain->ResizeBuffers(
			SwapChainBufferCount,
			AppWindow->GetClientWidth(),
			AppWindow->GetClientHeight(),
			BackBufferFormat,
			DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH
		));

		CurrentBackBufferIndex = 0u;

		CD3DX12_CPU_DESCRIPTOR_HANDLE RenderTargetViewHeapHandle(RenderTargetViewHeap->GetCPUDescriptorHandleForHeapStart());
		for (uint32 Idx = 0u; Idx < SwapChainBufferCount; ++Idx)
		{
			ThrowIfFailed(SwapChain->GetBuffer(Idx, IID_PPV_ARGS(&SwapChainBuffers[Idx])));
			Device->CreateRenderTargetView(SwapChainBuffers[Idx].Get(), nullptr, RenderTargetViewHeapHandle);
			RenderTargetViewHeapHandle.Offset(1, RenderTargetViewDescriptorSize);
		}

		// Create depth stencil buffer and view
		D3D12_RESOURCE_DESC DepthStencilDesc = 
		{
			.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D,
			.Alignment = 0,
			.Width = AppWindow->GetClientWidth(),
			.Height = AppWindow->GetClientHeight(),
			.DepthOrArraySize = 1,
			.MipLevels = 1,
			.Format = DXGI_FORMAT_R24G8_TYPELESS,
			.SampleDesc = { 1, 0 },
			.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN,
			.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL,
		};

		D3D12_CLEAR_VALUE DepthStencilClearValue = 
		{
			.Format = DepthStencilFormat,
			.DepthStencil = { 1.0f, 0 }
		};

		auto HeapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
		ThrowIfFailed(Device->CreateCommittedResource(
			&HeapProperties,
			D3D12_HEAP_FLAG_NONE,
			&DepthStencilDesc,
			D3D12_RESOURCE_STATE_COMMON,
			&DepthStencilClearValue,
			IID_PPV_ARGS(DepthStencilBuffer.GetAddressOf())
		));

		// Create descriptor of mip level 0 of entire resource using the format of the resource
		D3D12_DEPTH_STENCIL_VIEW_DESC DepthStencilViewDesc =
		{
			.Format = DepthStencilFormat,
			.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D,
			.Flags = D3D12_DSV_FLAG_NONE,
			.Texture2D = D3D12_TEX2D_DSV{ 0u }
		};

		Device->CreateDepthStencilView(DepthStencilBuffer.Get(), &DepthStencilViewDesc, DepthStencilView());

		auto CommonToDepthWriteTransitionBarrier = CD3DX12_RESOURCE_BARRIER::Transition(DepthStencilBuffer.Get(), D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_DEPTH_WRITE);
		CommandList->ResourceBarrier(1, &CommonToDepthWriteTransitionBarrier);

		ThrowIfFailed(CommandList->Close());
		ID3D12CommandList* CommandLists[] = { CommandList.Get() };
		CommandQueue->ExecuteCommandLists(_countof(CommandLists), CommandLists);

		FlushCommandQueue();

		// Update viewport and client coverage area
		Viewport = D3D12_VIEWPORT
		{
			.TopLeftX = 0,
			.TopLeftY = 0,
			.Width = static_cast<float>(AppWindow->GetClientWidth()),
			.Height = static_cast<float>(AppWindow->GetClientHeight()),
			.MinDepth = 0.0f,
			.MaxDepth = 1.0
		};

		ScissorRect = { 0, 0, (int32)AppWindow->GetClientWidth(), (int32)AppWindow->GetClientHeight()};
	}

	void HD3DRenderer::FlushCommandQueue()
	{
		CurrentFence++;

		ThrowIfFailed(CommandQueue->Signal(Fence.Get(), CurrentFence));

		if (Fence->GetCompletedValue() < CurrentFence)
		{
			HANDLE EventHandle = CreateEventEx(nullptr, nullptr, false, EVENT_ALL_ACCESS);

			ThrowIfFailed(Fence->SetEventOnCompletion(CurrentFence, EventHandle));

			WaitForSingleObject(EventHandle, INFINITE);
			CloseHandle(EventHandle);
		}
	}

	ID3D12Resource* HD3DRenderer::CurrentBackBuffer() const
	{
		return SwapChainBuffers[CurrentBackBufferIndex].Get();
	}

	D3D12_CPU_DESCRIPTOR_HANDLE HD3DRenderer::CurrentBackBufferView() const
	{
		return CD3DX12_CPU_DESCRIPTOR_HANDLE(
			RenderTargetViewHeap->GetCPUDescriptorHandleForHeapStart(),
			CurrentBackBufferIndex,
			RenderTargetViewDescriptorSize
		);
	}

	D3D12_CPU_DESCRIPTOR_HANDLE HD3DRenderer::DepthStencilView() const
	{
		return DepthStencilViewHeap->GetCPUDescriptorHandleForHeapStart();
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

		MeshResource->VertexBufferGPU = HD3DResourceUtils::CreateDefaultBuffer(Device.Get(), CommandList.Get(), Vertices.data(), VBByteSize, MeshResource->VertexBufferUploader);
		MeshResource->IndexBufferGPU = HD3DResourceUtils::CreateDefaultBuffer(Device.Get(), CommandList.Get(), Indices.data(), IBByteSize, MeshResource->IndexBufferUploader);

		MeshResource->VertexByteStride = sizeof(HVertex);
		MeshResource->VertexBufferByteSize = VBByteSize;
		MeshResource->IndexFormat = DXGI_FORMAT_R16_UINT;
		MeshResource->IndexBufferByteSize = IBByteSize;

		HSubmeshInfo Submesh =
		{
			.IndexCount = { (uint32)Indices.size() },
			.StartIndex = 0u,
			.BaseVertex = 0u
		};

		MeshResource->Submeshes.insert(std::make_pair(TEXT("Box"), Submesh));
	}
}