#include "DirectXRenderer.h"
#include "DirectXRenderSystem.h"


namespace HopStep
{
	void HDirectX11Renderer::BeginFrame()
	{
		HCheck(System);

		// Todo: ColorClass
		float ClearColor[4];
		ClearColor[0] = 0.f;
		ClearColor[1] = 0.f;
		ClearColor[2] = 0.f;
		ClearColor[3] = 0.f;

		System->DeviceContext->ClearRenderTargetView(System->RenderTargetView, ClearColor);
	}

	void HDirectX11Renderer::EndFrame()
	{
		System->SwapChain->Present(System->bVsyncEnabled ? 1 : 0, 0);
	}
}