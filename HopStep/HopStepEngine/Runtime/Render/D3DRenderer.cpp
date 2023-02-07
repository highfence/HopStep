#include "D3DRenderer.h"
#include "D3DUtils.h"
#include "..\..\Core\Misc\Paths.h"
#include "..\..\Core\Misc\GenericMemory.h"	
#include "..\..\Core\GenericPlatform\GenericWindow.h"
#include "..\..\Core\Windows\WindowsWindow.h"

namespace HopStep
{
	HD3DRenderer::HD3DRenderer(TSharedPtr<HGenericWindow> AppWindowPtr)
	{
		HCheck(AppWindowPtr);
		AppWindow = AppWindowPtr;
		AspectRatio = static_cast<float>(AppWindow->GetClientWidth()) / static_cast<float>(AppWindow->GetClientHeight());
	}

	HD3DRenderer::~HD3DRenderer()
	{
	}

	bool HD3DRenderer::OnInit()
	{
		InitPipeline();
		LoadAssets();
		return true;
	}

	void HD3DRenderer::InitPipeline()
	{
		uint32 DXGIFactoryFlags = 0u;

#if defined(_DEBUG)
		{
			ComPtr<ID3D12Debug> DebugController;
			if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&DebugController))))
			{
				DebugController->EnableDebugLayer();
				DXGIFactoryFlags |= DXGI_CREATE_FACTORY_DEBUG;
			}
		}
#endif

		// Create Device
		ThrowIfFailed(CreateDXGIFactory2(DXGIFactoryFlags, IID_PPV_ARGS(&DXGIFactory)));
		
		// Todo: Add WARP adapter case
		ComPtr<IDXGIAdapter1> HardwareAdapter;
		HRenderPipelineUtils::GetHardwareAdapter(DXGIFactory.Get(), &HardwareAdapter);

		ThrowIfFailed(D3D12CreateDevice(HardwareAdapter.Get(), D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&Device)));

		// Describe and create command queue
		D3D12_COMMAND_QUEUE_DESC QueueDesc = 
		{
			.Type = D3D12_COMMAND_LIST_TYPE_DIRECT,
			.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE
		};

		ThrowIfFailed(Device->CreateCommandQueue(&QueueDesc, IID_PPV_ARGS(&CommandQueue)));

		// Describe and create swap chain
		DXGI_SWAP_CHAIN_DESC1 SwapChainDesc =
		{
			.Width = AppWindow->GetClientWidth(),
			.Height = AppWindow->GetClientHeight(),
			.Format = DXGI_FORMAT_R8G8B8A8_UNORM,
			.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT,
			.BufferCount = SwapChainBufferCount,
			.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD,
		};

		SwapChainDesc.SampleDesc.Count = 1;

		ComPtr<IDXGISwapChain1> SwapChain1;
		ThrowIfFailed(DXGIFactory->CreateSwapChainForHwnd(
			CommandQueue.Get(),
			HWindowsWindow::GetWindowHandle(),
			&SwapChainDesc,
			nullptr,
			nullptr,
			&SwapChain1
		));

		// Do not support full screen
		ThrowIfFailed(DXGIFactory->MakeWindowAssociation(HWindowsWindow::GetWindowHandle(), DXGI_MWA_NO_ALT_ENTER));

		ThrowIfFailed(SwapChain1.As(&SwapChain));
		FrameIndex = SwapChain->GetCurrentBackBufferIndex();

		// Create descriptor heaps.
		{
			D3D12_DESCRIPTOR_HEAP_DESC RtvHeapDesc
			{
				.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV,
				.NumDescriptors = SwapChainBufferCount,
				.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE,
			};
			ThrowIfFailed(Device->CreateDescriptorHeap(&RtvHeapDesc, IID_PPV_ARGS(&RtvHeap)));
			RtvDescriptorSize = Device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
		}

		// Create frame resources
		{
			CD3DX12_CPU_DESCRIPTOR_HANDLE RtvHandle(RtvHeap->GetCPUDescriptorHandleForHeapStart());

			for (uint32 N = 0; N < SwapChainBufferCount; ++N)
			{
				ThrowIfFailed(SwapChain->GetBuffer(N, IID_PPV_ARGS(&RenderTargets[N])));
				Device->CreateRenderTargetView(RenderTargets[N].Get(), nullptr, RtvHandle);
				RtvHandle.Offset(1, RtvDescriptorSize);
			}
		}

		ThrowIfFailed(Device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&CommandAllocator)));
	}

	void HD3DRenderer::LoadAssets()
	{
		// Create an empty root signature
		{
			CD3DX12_ROOT_SIGNATURE_DESC RootSignatureDesc;
			RootSignatureDesc.Init(0, nullptr, 0, nullptr, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

			ComPtr<ID3DBlob> Signature;
			ComPtr<ID3DBlob> Error;
			ThrowIfFailed(D3D12SerializeRootSignature(&RootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1, &Signature, &Error));
			ThrowIfFailed(Device->CreateRootSignature(0, Signature->GetBufferPointer(), Signature->GetBufferSize(), IID_PPV_ARGS(&RootSignature)));
		}

		// Create the pipeline state, including complies and loading shaders.
		{
			ComPtr<ID3DBlob> VertexShader;
			ComPtr<ID3DBlob> PixelShader;

			uint32 ComplieFlags = 0u;
#if defined(_DEBUG)
			ComplieFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

			HString ShaderPath = HPaths::ShaderPath().append(TEXT("\\shaders.hlsl"));
			ThrowIfFailed(D3DCompileFromFile(ShaderPath.c_str(), nullptr, nullptr, "VSMain", "vs_5_0", ComplieFlags, 0, &VertexShader, nullptr));
			ThrowIfFailed(D3DCompileFromFile(ShaderPath.c_str(), nullptr, nullptr, "PSMain", "ps_5_0", ComplieFlags, 0, &PixelShader, nullptr));

			D3D12_INPUT_ELEMENT_DESC InputElementDescs[] =
			{
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
				{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
			};

			D3D12_GRAPHICS_PIPELINE_STATE_DESC PSODesc = 
			{
				.pRootSignature = RootSignature.Get(),
				.VS = CD3DX12_SHADER_BYTECODE(VertexShader.Get()),
				.PS = CD3DX12_SHADER_BYTECODE(PixelShader.Get()),
				.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT),
				.SampleMask = UINT_MAX,
				.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT),
				.InputLayout = { InputElementDescs, _countof(InputElementDescs) },
				.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE,
				.NumRenderTargets = 1,
			};

			PSODesc.DepthStencilState.DepthEnable = FALSE;
			PSODesc.DepthStencilState.StencilEnable = FALSE;
			PSODesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
			PSODesc.SampleDesc.Count = 1;

			ThrowIfFailed(Device->CreateGraphicsPipelineState(&PSODesc, IID_PPV_ARGS(&PipelineState)));
		}

		ThrowIfFailed(Device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, CommandAllocator.Get(), PipelineState.Get(), IID_PPV_ARGS(&CommandList)));

		// Commandlist가 Recording state로 생성이 되었지만, 아직 record할 정보가 아무것도 없으므로 우선 close상태로 만들어준다.
		ThrowIfFailed(CommandList->Close());

		// Create vertex buffer
		{
			HVertex TriangleVertices[] =
			{
				{ { 0.0f, 0.25f * AspectRatio, 0.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
				{ { 0.25f, -0.25f * AspectRatio, 0.0f }, { 0.0f, 1.0f, 0.0f, 1.0f } },
				{ { -0.25f, -0.25f * AspectRatio, 0.0f }, { 0.0f, 0.0f, 1.0f, 1.0f } }
			};

			const uint32 VertexBufferSize = sizeof(TriangleVertices);

			// Note: 여기서는 코드를 간략하게 만들기 위해 upload heap을 사용하지만, 정상적인 방법으로 추천하지 않음.
			// GPU가 vertex를 필요로 할 때마다, upload head의 마샬링이 필요해질것이다. Default head usage에 대한 문서를 읽자.
			auto HeapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
			auto VertexBufferDesc = CD3DX12_RESOURCE_DESC::Buffer(VertexBufferSize);

			ThrowIfFailed(Device->CreateCommittedResource(
				&HeapProperties,
				D3D12_HEAP_FLAG_NONE,
				&VertexBufferDesc,
				D3D12_RESOURCE_STATE_GENERIC_READ,
				nullptr,
				IID_PPV_ARGS(&VertexBuffer)
			));

			// TriangleData를 VertexBuffer로 복사시켜주자.
			uint8* VertexData;
			CD3DX12_RANGE ReadRange(0, 0);
			ThrowIfFailed(VertexBuffer->Map(0, &ReadRange, reinterpret_cast<void**>(&VertexData)));
			HGenericMemory::MemCpy(VertexData, TriangleVertices, sizeof(TriangleVertices));
			VertexBuffer->Unmap(0, nullptr);

			// Intialize vertex buffer view
			VertexBufferView.BufferLocation = VertexBuffer->GetGPUVirtualAddress();
			VertexBufferView.StrideInBytes = sizeof(HVertex);
			VertexBufferView.SizeInBytes = VertexBufferSize;
		}

		// Create Synchronization objects. Wait until assets have been uploaded to the GPU.
		{
			ThrowIfFailed(Device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&Fence)));
			FenceValue = 1;

			FenceEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
			if (FenceEvent == nullptr)
			{
				ThrowIfFailed(HRESULT_FROM_WIN32(GetLastError()));
			}

			// CommandList가 execute하길 기다려준다.
			WaitForPreviousFrame();
		}
	}

	void HD3DRenderer::WaitForPreviousFrame()
	{
		// 프레임이 끝나기를 기다리는 것은 훌륭한 케이스가 아니며, 코드 단순성을 위해 만들어진 코드.
		// 나중에 D3D12HelloFrameBuffering을 보면서 이를 고칠 것.

		const uint64 FenceLocalValue = FenceValue;
		ThrowIfFailed(CommandQueue->Signal(Fence.Get(), FenceLocalValue));
		++FenceValue;

		if (Fence->GetCompletedValue() < FenceLocalValue)
		{
			ThrowIfFailed(Fence->SetEventOnCompletion(FenceLocalValue, FenceEvent));
			WaitForSingleObject(FenceEvent, INFINITE);
		}

		FrameIndex = SwapChain->GetCurrentBackBufferIndex();
	}
}