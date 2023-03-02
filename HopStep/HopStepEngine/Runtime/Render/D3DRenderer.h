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
		// D3D App Layer

		void DebugLogAdapters() const;

		float AspectRatio = 0.0f;
		static const uint32 SwapChainBufferCount = 2u;

		TSharedPtr<class HGenericWindow> AppWindow;
		TSharedPtr<class HGameView> ViewInfo;

		D3D12_VIEWPORT Viewport;
		D3D12_RECT ScissorRect;

		ComPtr<IDXGIFactory4> DXGIFactory;
		ComPtr<ID3D12Device> Device;
		ComPtr<IDXGISwapChain> SwapChain;

		ComPtr<ID3D12Fence> Fence;

		ComPtr<ID3D12CommandQueue> CommandQueue;
		ComPtr<ID3D12CommandAllocator> CommandAllocator;
		ComPtr<ID3D12GraphicsCommandList> CommandList;

		ComPtr<ID3D12Resource> SwapChainBuffers[SwapChainBufferCount];

		DXGI_FORMAT BackBufferFormat = DXGI_FORMAT_R8G8B8A8_UNORM;

		ComPtr<ID3D12DescriptorHeap> RenderTargetViewHeap;
		ComPtr<ID3D12DescriptorHeap> DepthStencilViewHeap;

		uint32 RenderTargetViewDescriptorSize = 0u;
		uint32 DepthStencilViewDescripotSize = 0u;
		uint32 CbvSrvUavDescriptorSize = 0u;

	private:
		// Inherited App Layer

		ComPtr<ID3D12DescriptorHeap> ConstantBufferViewHeap;
		ComPtr<ID3D12RootSignature> RootSignature;

		TUniquePtr<TUploadBuffer<HObjectConstantBuffer>> ObjectConstantBuffer = nullptr;

		ComPtr<ID3DBlob> VertexShaderByteCode;
		ComPtr<ID3DBlob> PixelShaderByteCode;

		TArray<D3D12_INPUT_ELEMENT_DESC> InputLayout;
	};
}