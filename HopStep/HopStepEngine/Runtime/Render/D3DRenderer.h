#pragma once
#include "DirectXIncludes.h"
#include "ID3DRenderer.h"

namespace HopStep
{
	struct HVertex
	{
		XMFLOAT3 Position;
		XMFLOAT4 Color;
	};

	class HD3DRenderer : public ID3DRenderer
	{
	public:

		HD3DRenderer(TSharedPtr<class HGenericWindow> AppWindowPtr);

		virtual ~HD3DRenderer();

		virtual bool OnInit() override;

	private:

		float AspectRatio = 0.0f;

		static constexpr uint8 SwapChainBufferCount = 2;

		TSharedPtr<class HGenericWindow> AppWindow;

		ComPtr<ID3D12Device> Device;
		ComPtr<IDXGIFactory4> DXGIFactory;
		ComPtr<IDXGISwapChain3> SwapChain;
		ComPtr<ID3D12DescriptorHeap> RtvHeap;
		ComPtr<ID3D12Resource> RenderTargets[SwapChainBufferCount];
		ComPtr<ID3D12RootSignature> RootSignature;
		ComPtr<ID3D12PipelineState> PipelineState;

		ComPtr<ID3D12CommandQueue> CommandQueue;
		ComPtr<ID3D12CommandAllocator> CommandAllocator;
		ComPtr<ID3D12GraphicsCommandList> CommandList;

		// Resources
		ComPtr<ID3D12Resource> VertexBuffer;
		D3D12_VERTEX_BUFFER_VIEW VertexBufferView;

		// Synchronization
		ComPtr<ID3D12Fence> Fence;
		uint64 FenceValue;
		HANDLE FenceEvent;

		uint32 RtvDescriptorSize;

		uint32 FrameIndex;

		void InitPipeline();
		void LoadAssets();
	};
}