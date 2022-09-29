#pragma once
#include "..\..\Core\HopStepCore.h"
#include "ReflectionMarco.h"
#include "ReflectionTest.generated.h"

namespace HopStep::CoreObject::Reflection
{
#if HopStep_UnitTest

	HCLASS()
	class HReflectionTest
	{
		DECLARE_CLASS_BODY(HReflectionTest);

		HPROPERTY();
		int32 A;

		HPROPERTY();
		int32 B;

		HPROPERTY();
		int32 C;
	};

#endif
}
