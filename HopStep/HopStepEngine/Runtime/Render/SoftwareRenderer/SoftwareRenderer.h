#pragma once
#include "Runtime/Render/Renderer.h"

namespace HopStep
{
	class HSoftwareRenderer : public IRenderer
	{
	public:

		HSoftwareRenderer();
			
		// IRenderer을(를) 통해 상속됨
		virtual void RenderScene(const class HSceneInterface* InScene, class HFrameBuffer& InFrameBuffer) override;

	};
}