#include "D3DRenderer.h"
#include "D3DUtils.h"

namespace HopStep
{
	HD3DRenderer::~HD3DRenderer()
	{
	}

	bool HD3DRenderer::InitDirect3D()
	{
#if defined(DEBUG) || defined(_DEBUG)
		{
			ComPtr<ID3D12Debug> DebugController;
			ThrowIfFailed(D3D12GetDebugInterface(IID_PPV_ARGS(&DebugController)));
			DebugController->EnableDebugLayer();
		}
#endif

		return false;
	}
}