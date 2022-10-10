#pragma once
#include "..\HopStepEngine\Core\HopStepCore.h"
#include "..\HopStepEngine\CoreObject\Reflection\ReflectionMarco.h"
#include "..\HopStepEngine\Intermediate\ReflectionTest.generated.h"

namespace HopStep::CoreObject::Reflection
{
#if HopStep_UnitTest

	HEnum();
	enum class EReflectionTestEnum
	{
		Test1,
		Test2,
		Max
	};


	HCLASS();
	class HInnerClassTest
	{
		DECLARE_CLASS_BODY(HInnerClassTest);
		
	public:

		HPROPERTY();
		float InnerA;

		int32 InnerPadding;

		HPROPERTY();
		int8 InnerB;

	};

	HCLASS();
	class HReflectionTest
	{
		DECLARE_CLASS_BODY(HReflectionTest);

	public:

		HPROPERTY();
		int32 A;

		HPROPERTY();
		HChar B;

		int32 Padding;

		HPROPERTY();
		bool C;

		HPROPERTY();
		HString D;

		HPROPERTY();
		EReflectionTestEnum EnumTest;

		HPROPERTY();
		HInnerClassTest* InnerClassPtr;
	};

	HCLASS();
	class HStringPropertyTest
	{
		DECLARE_CLASS_BODY(HStringPropertyTest);

	public:

		HPROPERTY();
		int32 Prev;

		HPROPERTY();
		HString StringProperty;

		HPROPERTY();
		HChar Post;
	};

#endif
}
