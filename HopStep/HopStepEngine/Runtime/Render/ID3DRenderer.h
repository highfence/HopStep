#pragma once
#include "..\..\Core\HopStepOverrides.h"

namespace HopStep
{
	class ID3DRenderer
	{
	public:

		virtual ~ID3DRenderer() {}

		static ID3DRenderer* CreateD3DRenderer(TSharedPtr<class HGenericWindow> WindowPtr, TSharedPtr<class HGameView> CameraPtr);
		
		virtual bool OnInit() = 0;

		virtual void OnUpdate() = 0;

		virtual void OnRender() = 0;

		virtual void OnDestroy() = 0;
	};
}