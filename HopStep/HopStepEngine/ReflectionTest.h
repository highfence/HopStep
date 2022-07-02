#pragma once
#include "HopStepDefine.h"

namespace HopStep::CoreObject::Reflection
{
#if HopStep_UnitTest

	HCLASS()
	class HReflectionObjectTest
	{
	public:
		DECLARE_CLASS_BODY(HReflectionObjectTest);

		HPROPERTY();
		int32 A;

		HPROPERTY();
		int32 B;

		HPROPERTY();
		int32 C;

		friend void __Fill_Class_Property_HReflectionObjectTest(HClass* InStaticClass);
	};

#endif
}
