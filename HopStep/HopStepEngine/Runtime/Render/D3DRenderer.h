#pragma once
#include "DirectXIncludes.h"
#include "ID3DRenderer.h"
#include "D3DStructure.h"
#include "UploadBuffer.h"

namespace HopStep
{
	class HD3DRenderer : public ID3DRenderer
	{
	public:

		HD3DRenderer(TSharedPtr<class HGenericWindow> AppWindowPtr, TSharedPtr<class HGameView> CameraPtr);

		virtual ~HD3DRenderer();

		virtual bool OnInit() override;

		virtual void OnUpdate() override;

		virtual void OnRender() override;

		virtual void OnDestroy() override;

	private:

		uint32 FrameCounter = 0u;

		float AspectRatio = 0.0f;

		static constexpr uint8 SwapChainBufferCount = 2;
		static constexpr uint32 TextureWidth = 256;
		static constexpr uint32 TextureHeight = 256;
		static constexpr uint32 TexturePixelSize = 4;

		TSharedPtr<class HGenericWindow> AppWindow;
		TSharedPtr<class HGameView> ViewInfo;

		ComPtr<ID3D12Device> Device;
		ComPtr<IDXGIFactory4> DXGIFactory;
		ComPtr<IDXGISwapChain3> SwapChain;
		ComPtr<ID3D12DescriptorHeap> RtvHeap;
		ComPtr<ID3D12Resource> RenderTargets[SwapChainBufferCount];
		ComPtr<ID3D12RootSignature> RootSignature;
		ComPtr<ID3D12PipelineState> PipelineState;
		ComPtr<ID3D12DescriptorHeap> SrvHeap;
		ComPtr<ID3D12DescriptorHeap> CbvHeap;

		CD3DX12_VIEWPORT Viewport;
		CD3DX12_RECT ScissorRect;

		ComPtr<ID3D12CommandQueue> CommandQueue;
		ComPtr<ID3D12CommandAllocator> CommandAllocator;
		ComPtr<ID3D12GraphicsCommandList> CommandList;

		TUniquePtr<TUploadBuffer<HObjectConstantBuffer>> ObjectConstantBuffer = nullptr;

		// Resources
		ComPtr<ID3D12Resource> VertexBuffer;
		D3D12_VERTEX_BUFFER_VIEW VertexBufferView;
		ComPtr<ID3D12Resource> Texture;

		// Synchronization
		ComPtr<ID3D12Fence> Fence;
		uint64 FenceValue;
		HANDLE FenceEvent;

		uint32 RtvDescriptorSize;

		uint32 FrameIndex;

		void InitPipeline();

		void LoadAssets();

		void WaitForPreviousFrame();

		void PopulateCommandList();

		TArray<uint8> GenerateSampleTextureData();
	};
}