#pragma once
#include "HopStepDefine.h"

namespace HopStep::CoreObject::Reflection
{
#if HopStep_UnitTest

	class HReflectionObjectTest
	{
		HPROPERTY();
		int32 A;

		HPROPERTY();
		int32 B;

		HPROPERTY();
		int32 C;
	};

#endif
}
