#pragma once
#include "RenderSystem.h"
#include "DirectXIncludes.h"
#include <DirectXMath.h>

namespace HopStep
{
	class HRenderSystem : public IRenderSystem
	{
	public:

		HRenderSystem();

		virtual ~HRenderSystem();

		// IRenderSystem을(를) 통해 상속됨
		virtual bool Initialize() override;
		virtual void Shutdown() override;

		virtual bool Render() override;

	protected:

		// Todo: Fix this.
		class HModelClass* ModelClass;
		class HColorShaderClass* ColorShader;
		class HViewInfo* ViewInfo;

		bool bVsyncEnabled;
		uint32 VideoCardMemory;
		HString VideoCardDescription;

		IDXGISwapChain* SwapChain;
		ID3D11Device* Device;
		ID3D11DeviceContext* DeviceContext;

		ID3D11RenderTargetView* RenderTargetView;
		ID3D11Texture2D* DepthStencilBuffer;
		ID3D11DepthStencilState* DepthStencilState;
		ID3D11DepthStencilView* DepthStencilView;
		ID3D11RasterizerState* RasterState;

		XMMATRIX ProjectionMatrix;
		XMMATRIX WorldMatrix;
		XMMATRIX OrthoMatrix;

		friend class HDirectX11Renderer;
	};
}
