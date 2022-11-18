#pragma once

namespace HopStep
{
	class ISceneRenderer
	{
	public:

		static ISceneRenderer* Create();

		virtual void BeginFrame() = 0;
		virtual void EndFrame() = 0;
	};
}