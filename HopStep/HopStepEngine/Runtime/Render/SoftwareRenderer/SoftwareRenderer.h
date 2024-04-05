#pragma once
#include "Runtime/Render/Renderer.h"

namespace HopStep
{
	class HSoftwareRenderer : public IRenderer
	{
	public:

		HSoftwareRenderer();
			
		// IRenderer��(��) ���� ��ӵ�
		virtual void RenderScene(const class HSceneInterface* InScene, class HFrameBuffer& InFrameBuffer) override;

	};
}