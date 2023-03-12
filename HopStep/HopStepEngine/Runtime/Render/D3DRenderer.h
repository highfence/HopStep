#pragma once
#include "DirectXIncludes.h"
#include "ID3DRenderer.h"
#include "D3DStructure.h"
#include "UploadBuffer.h"
#include "D3DUtils.h"
#include "Core/GenericPlatform/GenericApplicationMessageHandler.h"

namespace HopStep
{
	class HD3DRenderer : public ID3DRenderer, public IInputHandleable
	{
	public:

		HD3DRenderer(TSharedPtr<class HGenericWindow> AppWindowPtr, TSharedPtr<class HGameView> CameraPtr);

		// ID3DRenderer interfaces
		virtual ~HD3DRenderer();

		virtual bool OnInit() override;

		virtual void OnUpdate() override;

		virtual void OnRender() override;

		virtual void OnDestroy() override;

		void OnResize();
		// ~ID3DRenderer interfaces

		// IInputHandeable interfaces
		virtual void OnKeyDown(uint64* Key) override;

		virtual void OnKeyUp(uint64* Key) override;
		// ~IInputHandeable interfaces

	private:
		// D3D App Layer
		void FlushCommandQueue();

		ID3D12Resource* CurrentBackBuffer() const;

		D3D12_CPU_DESCRIPTOR_HANDLE CurrentBackBufferView() const;

		D3D12_CPU_DESCRIPTOR_HANDLE DepthStencilView() const;

		void DebugLogAdapters() const;

		float AspectRatio = 0.0f;
		static const uint32 SwapChainBufferCount = 2u;

		TSharedPtr<class HGenericWindow> AppWindow;
		TSharedPtr<class HGameView> ViewInfo;

		D3D12_VIEWPORT Viewport;
		// Rasterizer 단계에서 제거하지 않을 영역
		D3D12_RECT ScissorRect;

		ComPtr<IDXGIFactory4> DXGIFactory;
		ComPtr<ID3D12Device> Device;
		ComPtr<IDXGISwapChain> SwapChain;

		ComPtr<ID3D12Fence> Fence;
		uint64 CurrentFence = 0ull;

		ComPtr<ID3D12CommandQueue> CommandQueue;
		ComPtr<ID3D12CommandAllocator> CommandAllocator;
		ComPtr<ID3D12GraphicsCommandList> CommandList;

		ComPtr<ID3D12Resource> SwapChainBuffers[SwapChainBufferCount];
		ComPtr<ID3D12Resource> DepthStencilBuffer;
		uint32 CurrentBackBufferIndex = 0u;

		DXGI_FORMAT BackBufferFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
		DXGI_FORMAT DepthStencilFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;

		ComPtr<ID3D12DescriptorHeap> RenderTargetViewHeap;
		ComPtr<ID3D12DescriptorHeap> DepthStencilViewHeap;

		uint32 RenderTargetViewDescriptorSize = 0u;
		uint32 DepthStencilViewDescripotSize = 0u;
		uint32 CbvSrvUavDescriptorSize = 0u;

	private:
		// Inherited App Layer
		void BuildMeshResource();

		ComPtr<ID3D12DescriptorHeap> ConstantBufferViewHeap;
		ComPtr<ID3D12RootSignature> RootSignature;

		TUniquePtr<TUploadBuffer<HObjectConstantBuffer>> ObjectConstantBuffer = nullptr;

		ComPtr<ID3DBlob> VertexShaderByteCode;
		ComPtr<ID3DBlob> PixelShaderByteCode;

		TArray<D3D12_INPUT_ELEMENT_DESC> InputLayout;

		TUniquePtr<HMeshResource> MeshResource = nullptr;
		ComPtr<ID3D12PipelineState> PSO = nullptr;

		float Theta;
		float Phi;
		float Radius;

		XMFLOAT4X4 World = HD3DMathUtils::Identity4x4();
		XMFLOAT4X4 View = HD3DMathUtils::Identity4x4();
		XMFLOAT4X4 Projection = HD3DMathUtils::Identity4x4();

		POINT LastMousePos;
	};
}