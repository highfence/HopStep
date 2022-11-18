#include "RenderSystem.h"
#include "SceneRenderer.h"
#include "DirectXRenderSystem.h"

namespace HopStep
{
	IRenderSystem* IRenderSystem::Create()
	{
		IRenderSystem* System = new HRenderSystem();

		return System;
	}

}