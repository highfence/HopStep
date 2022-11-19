#include "DirectXRenderer.h"
#include "DirectXRenderSystem.h"


namespace HopStep
{
	void HDirectX11Renderer::BeginFrame()
	{
		HCheck(System);

		// Todo: ColorClass
		constexpr float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f };

		System->DeviceContext->ClearRenderTargetView(System->RenderTargetView, ClearColor);
	}

	void HDirectX11Renderer::EndFrame()
	{
		System->SwapChain->Present(System->bVsyncEnabled ? 1 : 0, 0);
	}
}