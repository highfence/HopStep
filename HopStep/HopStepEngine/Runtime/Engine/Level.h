#pragma once
#include "Core\CoreExport.h"
#include "CoreObject\CoreObjectExport.h"

namespace HopStep
{
	class HLevel : public HObject
	{
	public:

		~HLevel();

		bool InitLevel();

		void Tick(float DeltaTime);
	};
}