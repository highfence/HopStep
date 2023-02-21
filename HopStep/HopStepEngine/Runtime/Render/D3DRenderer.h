#pragma once
#include "DirectXIncludes.h"
#include "ID3DRenderer.h"

namespace HopStep
{
	struct HVertex
	{
		XMFLOAT3 Position;
		XMFLOAT3 Normal;
		XMFLOAT2 UV;

		/*
		HVertex() = default;
		HVertex(XMFLOAT3& InPos, XMFLOAT3& InNormal, XMFLOAT2& InUV)
			: Position(InPos), Normal(InNormal), UV(InUV)
		{

		}
		*/
	};

	class HD3DRenderer : public ID3DRenderer
	{
	public:

		HD3DRenderer(TSharedPtr<class HGenericWindow> AppWindowPtr);

		virtual ~HD3DRenderer();

		virtual bool OnInit() override;

		virtual void OnUpdate() override;

		virtual void OnRender() override;

		virtual void OnDestroy() override;

	private:

		float AspectRatio = 0.0f;

		static constexpr uint8 SwapChainBufferCount = 2;
		static constexpr uint32 TextureWidth = 256;
		static constexpr uint32 TextureHeight = 256;
		static constexpr uint32 TexturePixelSize = 4;

		TSharedPtr<class HGenericWindow> AppWindow;

		ComPtr<ID3D12Device> Device;
		ComPtr<IDXGIFactory4> DXGIFactory;
		ComPtr<IDXGISwapChain3> SwapChain;
		ComPtr<ID3D12DescriptorHeap> RtvHeap;
		ComPtr<ID3D12Resource> RenderTargets[SwapChainBufferCount];
		ComPtr<ID3D12RootSignature> RootSignature;
		ComPtr<ID3D12PipelineState> PipelineState;
		ComPtr<ID3D12DescriptorHeap> SrvHeap;
		CD3DX12_VIEWPORT Viewport;
		CD3DX12_RECT ScissorRect;

		ComPtr<ID3D12CommandQueue> CommandQueue;
		ComPtr<ID3D12CommandAllocator> CommandAllocator;
		ComPtr<ID3D12GraphicsCommandList> CommandList;

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