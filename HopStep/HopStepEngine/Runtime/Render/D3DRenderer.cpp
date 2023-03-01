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
	{
		HCheck(AppWindowPtr);
		AppWindow = AppWindowPtr;
		ViewInfo = InView;
		AspectRatio = static_cast<float>(AppWindow->GetClientWidth()) / static_cast<float>(AppWindow->GetClientHeight());
		Viewport = CD3DX12_VIEWPORT(0.0f, 0.0f, static_cast<float>(AppWindow->GetClientWidth()), static_cast<float>(AppWindow->GetClientHeight()));
		ScissorRect = CD3DX12_RECT(0, 0, AppWindow->GetClientWidth(), AppWindow->GetClientHeight());
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

	void HD3DRenderer::OnUpdate()
	{
		XMMATRIX World = XMMATRIX(::DirectX::g_XMIdentityR0, ::DirectX::g_XMIdentityR1, ::DirectX::g_XMIdentityR2,::DirectX::g_XMIdentityR3);
		XMMATRIX View = ViewInfo->GetViewMatrix();
		XMMATRIX Proj = ViewInfo->GetProjectionMatrix(::DirectX::XM_PI / 3.0f, AspectRatio);
		XMMATRIX WorldViewProj = World * View * Proj;

		HObjectConstantBuffer CB;
		::DirectX::XMStoreFloat4x4(&CB.WorldViewProj, ::DirectX::XMMatrixTranspose(WorldViewProj));
		ObjectConstantBuffer->CopyData(0, &CB);
	}

	void HD3DRenderer::OnRender()
	{
		PopulateCommandList();

		// Execute Command list
		ID3D12CommandList* CommandLists[] = { CommandList.Get() };
		CommandQueue->ExecuteCommandLists(_countof(CommandLists), CommandLists);

		// Present the frame
		ThrowIfFailed(SwapChain->Present(1, 0));

		WaitForPreviousFrame();
	}

	void HD3DRenderer::OnDestroy()
	{
		WaitForPreviousFrame();

		CloseHandle(FenceEvent);
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

			D3D12_DESCRIPTOR_HEAP_DESC SrvHeapDesc =
			{
				.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV,
				.NumDescriptors = 1,
				.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE
			};
			ThrowIfFailed(Device->CreateDescriptorHeap(&SrvHeapDesc, IID_PPV_ARGS(&SrvHeap)));

			D3D12_DESCRIPTOR_HEAP_DESC CbvHeapDesc =
			{
				.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV,
				.NumDescriptors = 1,
				.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE,
				.NodeMask = 0
			};
			ThrowIfFailed(Device->CreateDescriptorHeap(&CbvHeapDesc, IID_PPV_ARGS(&CbvHeap)));

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

		// Create constant buffer
		{
			ObjectConstantBuffer = std::make_unique<TUploadBuffer<HObjectConstantBuffer>>(Device.Get(), 1, true);

			uint32 CBByteSize = ObjectConstantBuffer->GetElementByteSize();
			D3D12_GPU_VIRTUAL_ADDRESS CBAddress = ObjectConstantBuffer->Resource()->GetGPUVirtualAddress();

			// Address offset in constant buffer
			uint32 ObjectIndex = 0u;
			CBAddress += ObjectIndex * CBByteSize;

			D3D12_CONSTANT_BUFFER_VIEW_DESC CBDesc = 
			{
				.BufferLocation = CBAddress,
				.SizeInBytes = CBByteSize
			};

			Device->CreateConstantBufferView(&CBDesc, CbvHeap->GetCPUDescriptorHandleForHeapStart());
		}

		ThrowIfFailed(Device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&CommandAllocator)));
	}

	void HD3DRenderer::LoadAssets()
	{
		// Create the root signature
		{
			D3D12_FEATURE_DATA_ROOT_SIGNATURE FeatureData = 
			{
				.HighestVersion = D3D_ROOT_SIGNATURE_VERSION_1_1
			};

			CD3DX12_DESCRIPTOR_RANGE1 Ranges[1] = { CD3DX12_DESCRIPTOR_RANGE1() };
			Ranges[0].Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 0, 0, D3D12_DESCRIPTOR_RANGE_FLAG_DATA_STATIC);

			CD3DX12_ROOT_PARAMETER1 RootParameters[1] = { CD3DX12_ROOT_PARAMETER1() };
			RootParameters[0].InitAsDescriptorTable(1, &Ranges[0], D3D12_SHADER_VISIBILITY_PIXEL);

			D3D12_STATIC_SAMPLER_DESC Sampler =
			{
				.Filter = D3D12_FILTER_MIN_MAG_MIP_POINT,
				.AddressU = D3D12_TEXTURE_ADDRESS_MODE_BORDER,
				.AddressV = D3D12_TEXTURE_ADDRESS_MODE_BORDER,
				.AddressW = D3D12_TEXTURE_ADDRESS_MODE_BORDER,
				.MipLODBias = 0,
				.MaxAnisotropy = 0,
				.ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER,
				.BorderColor = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK,
				.MinLOD = 0.0f,
				.MaxLOD = D3D12_FLOAT32_MAX,
				.ShaderRegister = 0,
				.RegisterSpace = 0,
				.ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL
			};

			CD3DX12_VERSIONED_ROOT_SIGNATURE_DESC RootSignatureDesc;
			RootSignatureDesc.Init_1_1(_countof(RootParameters), RootParameters, 1, &Sampler, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

			ComPtr<ID3DBlob> Signature;
			ComPtr<ID3DBlob> Error;
			ThrowIfFailed(D3DX12SerializeVersionedRootSignature(&RootSignatureDesc, FeatureData.HighestVersion, &Signature, &Error));
			ThrowIfFailed(Device->CreateRootSignature(0, Signature->GetBufferPointer(), Signature->GetBufferSize(), IID_PPV_ARGS(&RootSignature)));
		}

		// Create the pipeline state, including complies and loading shaders.
		{
			ComPtr<ID3DBlob> VertexShader;
			ComPtr<ID3DBlob> PixelShader;
			ComPtr<ID3DBlob> ErrorMsg;

			uint32 ComplieFlags = 0u;
#if defined(_DEBUG)
			ComplieFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

			HString ShaderPath = HPaths::ShaderPath().append(TEXT("shaders.hlsl"));
			HRESULT ComplieResult = D3DCompileFromFile(ShaderPath.c_str(), nullptr, nullptr, "VSMain", "vs_5_0", ComplieFlags, 0, &VertexShader, &ErrorMsg);
			if (FAILED(ComplieResult))
			{
				if (ErrorMsg)
				{
					static wchar_t szBuffer[4096];
					_snwprintf_s(szBuffer, 4096, _TRUNCATE,
						L"%hs",
						(char*)ErrorMsg->GetBufferPointer());
					OutputDebugString(szBuffer);
					MessageBox(nullptr, szBuffer, L"Error", MB_OK);
					ErrorMsg->Release();
				}
				HCheck(false);
			}

			ComplieResult = D3DCompileFromFile(ShaderPath.c_str(), nullptr, nullptr, "PSMain", "ps_5_0", ComplieFlags, 0, &PixelShader, &ErrorMsg);
			if (FAILED(ComplieResult))
			{
				if (ErrorMsg)
				{
					static wchar_t szBuffer[4096];
					_snwprintf_s(szBuffer, 4096, _TRUNCATE,
						L"%hs",
						(char*)ErrorMsg->GetBufferPointer());
					OutputDebugString(szBuffer);
					MessageBox(nullptr, szBuffer, L"Error", MB_OK);
					ErrorMsg->Release();
				}
				HCheck(false);
			}

			D3D12_INPUT_ELEMENT_DESC InputElementDescs[] =
			{
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
				{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
				{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
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
		// ThrowIfFailed(CommandList->Close());

		// Create vertex buffer
		{
			HVertex TriangleVertices[] =
			{
				{ { 0.0f, 0.25f * AspectRatio, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.5f, 0.0f } },
				{ { 0.25f, -0.25f * AspectRatio, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f } },
				{ { -0.25f, -0.25f * AspectRatio, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f } }
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

		// Create texture resource
		// ComPtr은 CPU 객체이지만, 이 텍스쳐 리소스는 GPU에서 실행이 완료될 때까지 파괴되지 않아야 한다.
		// 이 메서드 끝 부분에 GPU Flush가 있으므로 리소스가 너무 일찍 파괴되지 않는 것을 보장한다.
		ComPtr<ID3D12Resource> TextureUploadHeap;
		{
			D3D12_RESOURCE_DESC TextureDesc =
			{
				.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D,
				.Width = TextureWidth,
				.Height = TextureHeight,
				.DepthOrArraySize = 1,
				.MipLevels = 1,
				.Format = DXGI_FORMAT_R8G8B8A8_UNORM,
				.Flags = D3D12_RESOURCE_FLAG_NONE
			};
			TextureDesc.SampleDesc.Count = 1;
			TextureDesc.SampleDesc.Quality = 0;

			auto TextureProperty = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
			ThrowIfFailed(Device->CreateCommittedResource(
				&TextureProperty,
				D3D12_HEAP_FLAG_NONE,
				&TextureDesc,
				D3D12_RESOURCE_STATE_COPY_DEST,
				nullptr,
				IID_PPV_ARGS(&Texture)
			));

			const uint64 UploadBufferSize = ::GetRequiredIntermediateSize(Texture.Get(), 0, 1);

			// Create GPU upload buffer
			auto UploadBufferProperty = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
			auto UploadBufferDesc = CD3DX12_RESOURCE_DESC::Buffer(UploadBufferSize);

			ThrowIfFailed(Device->CreateCommittedResource(
				&UploadBufferProperty,
				D3D12_HEAP_FLAG_NONE,
				&UploadBufferDesc,
				D3D12_RESOURCE_STATE_GENERIC_READ,
				nullptr,
				IID_PPV_ARGS(&TextureUploadHeap)
			));

			TArray<uint8> TextureRawData = GenerateSampleTextureData();

			D3D12_SUBRESOURCE_DATA TextureData =
			{
				.pData = &TextureRawData[0],
				.RowPitch = TextureWidth * TexturePixelSize,
				.SlicePitch = TextureData.RowPitch * TextureHeight
			};

			UpdateSubresources(CommandList.Get(), Texture.Get(), TextureUploadHeap.Get(), 0, 0, 1, &TextureData);

			{
				auto TransitionToPixelShaderResource = CD3DX12_RESOURCE_BARRIER::Transition(Texture.Get(), D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);
				CommandList->ResourceBarrier(1, &TransitionToPixelShaderResource);
			}

			D3D12_SHADER_RESOURCE_VIEW_DESC SrvDesc =
			{
				.Format = TextureDesc.Format,
				.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D,
				.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING
			};
			SrvDesc.Texture2D.MipLevels = 1;
			Device->CreateShaderResourceView(Texture.Get(), &SrvDesc, SrvHeap->GetCPUDescriptorHandleForHeapStart());
		}

		ThrowIfFailed(CommandList->Close());
		ID3D12CommandList* CommandLists[] = { CommandList.Get() };
		CommandQueue->ExecuteCommandLists(_countof(CommandLists), CommandLists);

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

	void HD3DRenderer::PopulateCommandList()
	{
		// CommandAllocator는 관련 CommandList가 GPU에서 실행을 완료한 경우에 Reset 할 수 있다.
		// Fence를 이용하여 GPU 실행 진행률을 판단해야한다. (?)
		ThrowIfFailed(CommandAllocator->Reset());

		// 그러나 ExecuteCommandList()가 특정 CommandList에서 호출되면 언제든지 해당 CommandList는 Reset될 수 있으며, 반드시 re-recoding하기 전이여야 한다.
		ThrowIfFailed(CommandList->Reset(CommandAllocator.Get(), PipelineState.Get()));

		CommandList->SetGraphicsRootSignature(RootSignature.Get());

		ID3D12DescriptorHeap* Heaps[] = { SrvHeap.Get() };
		CommandList->SetDescriptorHeaps(_countof(Heaps), Heaps);

		CommandList->SetGraphicsRootDescriptorTable(0, SrvHeap->GetGPUDescriptorHandleForHeapStart());
		CommandList->RSSetViewports(1, &Viewport);
		CommandList->RSSetScissorRects(1, &ScissorRect);

		{
			auto TransitionToRenderTarget = CD3DX12_RESOURCE_BARRIER::Transition(RenderTargets[FrameIndex].Get(), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);
			CommandList->ResourceBarrier(1, &TransitionToRenderTarget);
		}

		CD3DX12_CPU_DESCRIPTOR_HANDLE RtvHandle(RtvHeap->GetCPUDescriptorHandleForHeapStart(), FrameIndex, RtvDescriptorSize);
		CommandList->OMSetRenderTargets(1, &RtvHandle, FALSE, nullptr);

		// Record Commands
		const float ClearColor[] = { 0.0f, 0.2f, 0.4f, 1.0f };
		CommandList->ClearRenderTargetView(RtvHandle, ClearColor, 0, nullptr);
		CommandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		CommandList->IASetVertexBuffers(0, 1, &VertexBufferView);
		CommandList->DrawInstanced(3, 1, 0, 0);

		// Swap buffer
		{
			auto TransitionToPresent = CD3DX12_RESOURCE_BARRIER::Transition(RenderTargets[FrameIndex].Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);
			CommandList->ResourceBarrier(1, &TransitionToPresent);
		}
		ThrowIfFailed(CommandList->Close());
	}

	TArray<uint8> HD3DRenderer::GenerateSampleTextureData()
	{
		const uint32 RowPitch = TextureWidth * TexturePixelSize;
		const uint32 CellPitch = RowPitch >> 3;	 // Checkerboard texture cell width size
		const uint32 CellHeight = TextureWidth >> 3; // Checkerboard texture cell height size
		const uint32 TextureSize = RowPitch * TextureHeight;

		TArray<uint8> Data(TextureSize);
		uint8* DataPtr = &Data[0];

		for (uint32 N = 0; N < TextureSize; N += TexturePixelSize)
		{
			uint32 X = N % RowPitch;
			uint32 Y = N / RowPitch;
			uint32 I = X / CellPitch;
			uint32 J = Y / CellHeight;

			if (I % 2 == J % 2)
			{
				DataPtr[N] = 0x00; 
				DataPtr[N + 1] = 0x00; 
				DataPtr[N + 2] = 0x00; 
				DataPtr[N + 3] = 0xff; 
			}
			else
			{
				DataPtr[N] = 0xff; 
				DataPtr[N + 1] = 0xff; 
				DataPtr[N + 2] = 0xff; 
				DataPtr[N + 3] = 0xff; 
			}
		}

		return Data;
	}
}