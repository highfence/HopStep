#include "ID3DRenderer.h"
#include "D3DRenderer.h"

namespace HopStep
{
	ID3DRenderer* ID3DRenderer::CreateD3DRenderer()
	{
		return new HD3DRenderer();
	}
}