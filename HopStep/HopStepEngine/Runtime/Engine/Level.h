#pragma once
#include "Core\CoreExport.h"
#include "CoreObject\CoreObjectExport.h"
#include "Intermediate\Level.generated.h"

namespace HopStep
{
	HCLASS();
	class HLevel : public HObject
	{
		DECLARE_CLASS_BODY(HLevel)

	public:

		~HLevel();

		bool InitLevel();

		void Tick(float DeltaTime);
	};
}
