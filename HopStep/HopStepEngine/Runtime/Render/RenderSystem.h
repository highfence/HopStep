#pragma once
#include "..\..\Core\CoreExport.h"

namespace HopStep
{
	class IRenderSystem
	{
	public:

		static IRenderSystem* Create();

		virtual bool Initialize() = 0;
		virtual void Shutdown() = 0;

		virtual bool Render() = 0;
	};
}