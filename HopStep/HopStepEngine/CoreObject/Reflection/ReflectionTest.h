#pragma once
#include "..\HopStepEngine\Core\CoreExport.h"
#include "..\HopStepEngine\CoreObject\Reflection\ReflectionMacro.h"
#include "..\HopStepEngine\CoreObject\Object\Object.h"
#include "..\HopStepEngine\Intermediate\ReflectionTest.generated.h"

namespace HopStep
{
#if HopStep_UnitTest

	HENUM();
	enum class EReflectionTestEnum
	{
		Test1,
		Test2,
		Max
	};


	HCLASS();
	class HInnerClassTest
	{
		DECLARE_CLASS_BODY(HInnerClassTest);;
		
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

	HCLASS();
	class HInheritanceTest : public HReflectionTest
	{
		DECLARE_CLASS_BODY(HInheritanceTest);

	public:

		HPROPERTY();
		int16 InheritanceProperty;
	};

	HCLASS();
	class HObjectInheritedTest : public HObjectBase
	{
		DECLARE_CLASS_BODY(HObjectInheritedTest);

	public:

	};

	HCLASS();
	class HFunctionTestObject
	{
		DECLARE_CLASS_BODY(HFunctionTestObject);

	public:

		HFUNCTION();
		int32 Add(int32 A, int32 B);

		int32 B;
		int32 C;

		HFUNCTION();
		int32 AddBC();

		// Todo : support reference parameter for HFUNCTION
		/*
		HFUNCTION();
		void AddWithParamter(int32& OutParam);
		*/
	};

	HCLASS();
	class HContainerReflectionTestObject
	{
		DECLARE_CLASS_BODY(HContainerReflectionTestObject);

	public:

		HPROPERTY();
		TArray<int32> ArrayProperty;

		HPROPERTY();
		TArray<HObject*> ObjectArrayProperty;
	};

	HCLASS();
	class HObjectDerivedTestObject : public HObject
	{
		DECLARE_CLASS_BODY(HObjectDerivedTestObject);

	public:

		HPROPERTY();
		int32 IntPropA;

		HPROPERTY();
		HString StringPropB;

		HPROPERTY();
		bool BooleanPropC;
	};

	HCLASS();
	class HObjectContainTestObject : public HObject
	{
		DECLARE_CLASS_BODY(HObjectContainTestObject);

	public:

		HPROPERTY();
		HObject* PropObject;

		void SetPropObject(HAny& InContainer, const HAny& InValue)
		{
			HObjectContainTestObject* Object = std::any_cast<HObjectContainTestObject*>(InContainer);
			Object->PropObject = std::any_cast<HObject*>(InValue);
		}

		void GetPropObject(const HAny& InContainer, HAny& OutValue)
		{
			HObjectContainTestObject* Object = std::any_cast<HObjectContainTestObject*>(InContainer);
			OutValue = Object->PropObject;
		}
	};
#endif
}
