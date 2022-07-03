#pragma once
#include "HopStepDefine.h"

namespace HopStep::CoreObject::Reflection
{
#if HopStep_UnitTest

	HCLASS()
	class HReflectionObjectTest
	{
		DECLARE_CLASS_BODY(HReflectionObjectTest);

		HPROPERTY();
		int32 A;

		HPROPERTY();
		int32 B;

		HPROPERTY();
		int32 C;
	};

#endif
}
