#include "D3DRenderer.h"
#include "D3DUtils.h"
#include "..\..\Core\GenericPlatform\GenericWindow.h"
#include "..\..\Core\Windows\WindowsWindow.h"

namespace HopStep
{
	HD3DRenderer::HD3DRenderer(TSharedPtr<HGenericWindow> AppWindowPtr)
	{
		HCheck(AppWindowPtr);
		AppWindow = AppWindowPtr;
	}

	HD3DRenderer::~HD3DRenderer()
	{
	}

	bool HD3DRenderer::OnInit()
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
		return true;
	}
}