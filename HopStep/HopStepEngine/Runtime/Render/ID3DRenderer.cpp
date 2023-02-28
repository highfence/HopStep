#include "ID3DRenderer.h"
#include "D3DRenderer.h"

namespace HopStep
{
	ID3DRenderer* ID3DRenderer::CreateD3DRenderer(TSharedPtr<class HGenericWindow> WindowPtr, TSharedPtr<class HGameView> CameraPtr)
	{
		return new HD3DRenderer(WindowPtr, CameraPtr);
	}
}