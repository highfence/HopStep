#pragma once
#include "DirectXIncludes.h"
#include "ID3DRenderer.h"

namespace HopStep
{
	class HD3DRenderer : public ID3DRenderer
	{
	public:

		HD3DRenderer(TSharedPtr<class HGenericWindow> AppWindowPtr);

		virtual ~HD3DRenderer();

		virtual bool OnInit() override;

	private:

		static constexpr uint8 SwapChainBufferCount = 2;

		TSharedPtr<class HGenericWindow> AppWindow;

		ComPtr<ID3D12Device> Device;
		ComPtr<IDXGIFactory4> DXGIFactory;
		ComPtr<ID3D12CommandQueue> CommandQueue;
		ComPtr<IDXGISwapChain3> SwapChain;
		ComPtr<ID3D12DescriptorHeap> RtvHeap;
		ComPtr<ID3D12Resource> RenderTargets[SwapChainBufferCount];
		ComPtr<ID3D12CommandAllocator> CommandAllocator;
		ComPtr<ID3D12RootSignature> RootSignature;
		uint32 RtvDescriptorSize;

		uint32 FrameIndex;

		void InitPipeline();
		void LoadAssets();
	};
}