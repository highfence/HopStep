#pragma once
#include "..\..\Core\HopStepOverrides.h"

namespace HopStep
{
	class ID3DRenderer
	{
	public:

		virtual ~ID3DRenderer() {}

		static ID3DRenderer* CreateD3DRenderer(TSharedPtr<class HGenericWindow> WindowPtr);
		
		virtual bool OnInit() = 0;
	};
}