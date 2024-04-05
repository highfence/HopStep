#pragma once

namespace HopStep
{
	class IRenderer
	{
	public:

		static IRenderer* CreateRenderer();

		virtual ~IRenderer() {};

		virtual void RenderScene(const class HSceneInterface* InScene, class HFrameBuffer& InFrameBuffer) = 0;
	};
}