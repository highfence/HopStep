#pragma once
#include "SceneRenderer.h"

namespace HopStep
{
	class HDirectX11Renderer : public ISceneRenderer
	{
	public:

		// ISceneRenderer��(��) ���� ��ӵ�
		virtual void BeginFrame() override;
		virtual void EndFrame() override;

		class HRenderSystem* System;

		// Renderer must be stateless.
	};
}