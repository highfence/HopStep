#pragma once
#include "Core\HopStepCore.h"
#include "ReflectionMarco.h"
#include "ReflectionTest.generated.h"

namespace HopStep::CoreObject::Reflection
{
#if HopStep_UnitTest

	HCLASS()
	class HReflectionTest
	{
		DECLARE_CLASS_BODY(HReflectionTest);

	public:

		HPROPERTY();
		int32 A;

		HPROPERTY();
		int32 B;

		int32 Padding;

		HPROPERTY();
		bool C;

		HPROPERTY();
		int32 D;
	};

#endif
}
