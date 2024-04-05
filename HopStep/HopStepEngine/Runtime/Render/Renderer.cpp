#include "Renderer.h"
#include "Runtime/Render/SoftwareRenderer/SoftwareRenderer.h"

namespace HopStep
{
	IRenderer* IRenderer::CreateRenderer()
	{
		return new HSoftwareRenderer();
	}
}
