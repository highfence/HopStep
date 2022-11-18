#include "DirectXRenderSystem.h"
#include "SceneRenderer.h"
#include "DirectXRenderer.h"

namespace HopStep
{
	constexpr bool bVsync = false;
	constexpr float ScreenDepth = 1000.0f;
	constexpr float ScreenNear = 0.1f;

	HRenderSystem::HRenderSystem()
		: SwapChain(nullptr)
		, Device(nullptr)
		, DeviceContext(nullptr)
		, RenderTargetView(nullptr)
		, DepthStencilBuffer(nullptr)
		, DepthStencilState(nullptr)
		, DepthStencilView(nullptr)
		, RasterState(nullptr)
		, bVsyncEnabled(bVsync)
		, VideoCardMemory(0)
	{
		ProjectionMatrix = DirectX::XMMatrixIdentity();
		WorldMatrix = DirectX::XMMatrixIdentity();
		OrthoMatrix = DirectX::XMMatrixIdentity();
	}

	HRenderSystem::~HRenderSystem()
	{
		Shutdown();
	}

	bool HRenderSystem::Initialize()
	{
		// 일단 래스터텍을 따라해본다. 정리는 나중에.
		HRESULT Result;

		IDXGIFactory* Factory;
		{
			Result = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&Factory);
			if (FAILED(Result)) return false;
		}

		IDXGIAdapter* Adapter;
		{
			Result = Factory->EnumAdapters(0, &Adapter);
			if (FAILED(Result)) return false;
		}

		IDXGIOutput* AdapterOutput;
		{
			Result = Adapter->EnumOutputs(0, &AdapterOutput);
			if (FAILED(Result)) return false;
		}

		unsigned int NumModes = 0u;
		{
			Result = AdapterOutput->GetDisplayModeList(DXGI_FORMAT_B8G8R8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &NumModes, NULL);
			if (FAILED(Result)) return false;
		}

		DXGI_MODE_DESC* DisplayModeList = new DXGI_MODE_DESC[NumModes];
		{
			Result = AdapterOutput->GetDisplayModeList(DXGI_FORMAT_B8G8R8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &NumModes, DisplayModeList);
			if (FAILED(Result)) return false;
		}

		unsigned int Numerator = 0u; 
		unsigned int Denominator = 0u;
		{
			for (uint32 Idx = 0; Idx < NumModes; ++Idx)
			{
#pragma warning(disable:6385)
				DXGI_MODE_DESC& DisplayMode = DisplayModeList[Idx];
#pragma warning(default:6385)
				if (DisplayMode.Width == ClientWidth && DisplayMode.Height == ClientHeight)
				{
					Numerator = DisplayMode.RefreshRate.Numerator;
					Denominator = DisplayMode.RefreshRate.Denominator;
				}
			}
		}

		DXGI_ADAPTER_DESC AdapterDesc;
		{
			Result = Adapter->GetDesc(&AdapterDesc);
			if (FAILED(Result)) return false;
		}

		VideoCardMemory = (int32)(AdapterDesc.DedicatedVideoMemory / (1024 * 1024));
		VideoCardDescription = HString(AdapterDesc.Description);

		delete[] DisplayModeList;
		SAFE_RELEASE(AdapterOutput);
		SAFE_RELEASE(Adapter);
		SAFE_RELEASE(Factory);

		DXGI_SWAP_CHAIN_DESC SwapChainDesc;
		{
			HGenericMemory::MemZero(&SwapChainDesc, sizeof(SwapChainDesc));
			SwapChainDesc.BufferCount = 1;
			SwapChainDesc.BufferDesc.Width = ClientWidth;
			SwapChainDesc.BufferDesc.Height = ClientHeight;
			SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R10G10B10A2_UNORM;

			SwapChainDesc.BufferDesc.RefreshRate.Numerator = bVsyncEnabled ? Numerator : 0;
			SwapChainDesc.BufferDesc.RefreshRate.Denominator = bVsyncEnabled ? Denominator : 0;

			SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			SwapChainDesc.OutputWindow = GWindowHandle;

			SwapChainDesc.SampleDesc.Count = 1;
			SwapChainDesc.SampleDesc.Quality = 0;
			SwapChainDesc.Windowed = true;

			SwapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
			SwapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

			SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
			SwapChainDesc.Flags = 0;
		}

		D3D_FEATURE_LEVEL FeatureLevel = D3D_FEATURE_LEVEL_11_0;
		UINT CreationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#if _DEBUG
		CreationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

		Result = D3D11CreateDeviceAndSwapChain(
			NULL,
			D3D_DRIVER_TYPE_HARDWARE,
			NULL,
			CreationFlags,
			&FeatureLevel,
			1,
			D3D11_SDK_VERSION,
			&SwapChainDesc,
			&SwapChain,
			&Device,
			NULL,
			&DeviceContext);

		if (FAILED(Result)) return false;

		ID3D11Texture2D* BackBufferPtr;
		{
			Result = SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&BackBufferPtr);
			if (FAILED(Result)) return false;

			Result = Device->CreateRenderTargetView(BackBufferPtr, NULL, &RenderTargetView);
			if (FAILED(Result)) return false;
		}
		SAFE_RELEASE(BackBufferPtr);

		D3D11_TEXTURE2D_DESC DepthBufferDesc;
		{
			HGenericMemory::MemZero(&DepthBufferDesc, sizeof(DepthBufferDesc));
			DepthBufferDesc.Width = ClientWidth;
			DepthBufferDesc.Height = ClientHeight;

			DepthBufferDesc.MipLevels = 1;
			DepthBufferDesc.ArraySize = 1;
			DepthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
			DepthBufferDesc.SampleDesc.Count = 1;
			DepthBufferDesc.SampleDesc.Quality = 0;
			DepthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
			DepthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
			DepthBufferDesc.CPUAccessFlags = 0;
			DepthBufferDesc.MiscFlags = 0;
		}

		Result = Device->CreateTexture2D(&DepthBufferDesc, NULL, &DepthStencilBuffer);
		if (FAILED(Result)) return false;

		D3D11_DEPTH_STENCIL_DESC DepthStencilDesc;
		{
			HGenericMemory::MemZero(&DepthStencilDesc, sizeof(DepthStencilDesc));

			DepthStencilDesc.DepthEnable = true;
			DepthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
			DepthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

			DepthStencilDesc.StencilEnable = true;
			DepthStencilDesc.StencilReadMask = 0xFF;
			DepthStencilDesc.StencilWriteMask = 0xFF;

			DepthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
			DepthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
			DepthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
			DepthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

			DepthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
			DepthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
			DepthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
			DepthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
		}

		Result = Device->CreateDepthStencilState(&DepthStencilDesc, &DepthStencilState);
		if (FAILED(Result)) return false;

		DeviceContext->OMSetDepthStencilState(DepthStencilState, 1);

		D3D11_DEPTH_STENCIL_VIEW_DESC DepthStencilViewDesc;
		{
			HGenericMemory::MemZero(&DepthStencilViewDesc, sizeof(DepthStencilViewDesc));

			DepthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
			DepthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
			DepthStencilViewDesc.Texture2D.MipSlice = 0;
		}

		Result = Device->CreateDepthStencilView(DepthStencilBuffer, &DepthStencilViewDesc, &DepthStencilView);
		if (FAILED(Result)) return false;

		DeviceContext->OMSetRenderTargets(1, &RenderTargetView, DepthStencilView);

		D3D11_RASTERIZER_DESC RasterDesc;
		{
			RasterDesc.AntialiasedLineEnable = false;
			RasterDesc.CullMode = D3D11_CULL_BACK;
			RasterDesc.DepthBias = 0;
			RasterDesc.DepthBiasClamp = 0.0f;
			RasterDesc.DepthClipEnable = true;
			RasterDesc.FillMode = D3D11_FILL_SOLID;
			RasterDesc.FrontCounterClockwise = false;
			RasterDesc.MultisampleEnable = false;
			RasterDesc.ScissorEnable = false;
			RasterDesc.SlopeScaledDepthBias = 0.0f;
		}

		Result = Device->CreateRasterizerState(&RasterDesc, &RasterState);
		if (FAILED(Result)) return false;

		DeviceContext->RSSetState(RasterState);

		D3D11_VIEWPORT Viewport;
		{
			Viewport.Width = (float)ClientWidth;
			Viewport.Height = (float)ClientHeight;
			Viewport.MinDepth = 0.0f;
			Viewport.MaxDepth = 1.0f;
			Viewport.TopLeftX = 0.0f;
			Viewport.TopLeftY = 0.0f;
		}

		DeviceContext->RSSetViewports(1, &Viewport);

		float FieldOfView, ScreenAspect;
		{
			FieldOfView = (float)DirectX::XM_PI / 4.0f;
			ScreenAspect = (float)ClientWidth / (float)ClientHeight;
		}
		ProjectionMatrix = DirectX::XMMatrixPerspectiveLH(FieldOfView, ScreenAspect, ScreenNear, ScreenDepth);
		WorldMatrix = DirectX::XMMatrixIdentity();
		OrthoMatrix = DirectX::XMMatrixOrthographicLH((float)ClientWidth, (float)ClientHeight, ScreenNear, ScreenDepth);

		return true;
	}

	void HRenderSystem::Shutdown()
	{
		if (SwapChain)
		{
			SwapChain->SetFullscreenState(false, NULL);
		}

		SAFE_RELEASE(RasterState);
		SAFE_RELEASE(DepthStencilView);
		SAFE_RELEASE(DepthStencilState);
		SAFE_RELEASE(DepthStencilBuffer);
		SAFE_RELEASE(RenderTargetView);
		SAFE_RELEASE(DeviceContext);
		SAFE_RELEASE(Device);
		SAFE_RELEASE(SwapChain);
	}

	bool HRenderSystem::Render()
	{
		ISceneRenderer* Renderer = ISceneRenderer::Create();
		{
			HDirectX11Renderer* DX11Renderer = dynamic_cast<HDirectX11Renderer*>(Renderer);
			DX11Renderer->System = this;
		}

		Renderer->BeginFrame();
		Renderer->EndFrame();

		delete Renderer;
		return true;
	}
}