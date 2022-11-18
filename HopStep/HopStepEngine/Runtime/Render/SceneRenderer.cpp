#include "SceneRenderer.h"
#include "DirectXRenderer.h"

namespace HopStep
{
	ISceneRenderer* ISceneRenderer::Create()
	{
		return new HDirectX11Renderer();
	}
}