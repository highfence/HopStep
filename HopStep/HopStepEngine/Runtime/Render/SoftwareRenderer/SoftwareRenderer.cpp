#include "SoftwareRenderer.h"
#include "Runtime/Render/FrameBuffer.h"
#include "Runtime/Engine/SceneInterface.h"

namespace HopStep
{
	HSoftwareRenderer::HSoftwareRenderer()
	{
	}

	void HSoftwareRenderer::RenderScene(const HSceneInterface* InScene, HFrameBuffer& InFrameBuffer)
	{
		// Clear Target
		InFrameBuffer.ClearBuffers();
	}
}