#include "HopStep.h"
#include "ReflectionTest.generated.h"
#include "CoreObject\Reflection\ReflectionTest.h"

using namespace HopStep::CoreObject::Reflection;

void HInnerClassTest::__Fill_Class_Property_HInnerClassTest(HClass* InStaticClass)
{
	HStructBuilder::AddProperty<HInnerClassTest, float, HClassProperty>(InStaticClass, TEXT("InnerA"), &HInnerClassTest::InnerA);
	HStructBuilder::AddProperty<HInnerClassTest, int8, HNumericProperty>(InStaticClass, TEXT("InnerB"), &HInnerClassTest::InnerB);
}


IMPLEMENT_CLASS(HInnerClassTest);

void HReflectionTest::__Fill_Class_Property_HReflectionTest(HClass* InStaticClass)
{
	HStructBuilder::AddProperty<HReflectionTest, int32, HNumericProperty>(InStaticClass, TEXT("A"), &HReflectionTest::A);
	HStructBuilder::AddProperty<HReflectionTest, HChar, HCharacterProperty>(InStaticClass, TEXT("B"), &HReflectionTest::B);
	HStructBuilder::AddProperty<HReflectionTest, bool, HBooleanProperty>(InStaticClass, TEXT("C"), &HReflectionTest::C);
	HStructBuilder::AddProperty<HReflectionTest, HString, HStringProperty>(InStaticClass, TEXT("D"), &HReflectionTest::D);
	HStructBuilder::AddProperty<HReflectionTest, EReflectionTestEnum, HEnumProperty>(InStaticClass, TEXT("EnumTest"), &HReflectionTest::EnumTest);
	HStructBuilder::AddProperty<HReflectionTest, HInnerClassTest*, HClassProperty>(InStaticClass, TEXT("InnerClassPtr"), &HReflectionTest::InnerClassPtr);
}


IMPLEMENT_CLASS(HReflectionTest);

void HStringPropertyTest::__Fill_Class_Property_HStringPropertyTest(HClass* InStaticClass)
{
	HStructBuilder::AddProperty<HStringPropertyTest, int32, HNumericProperty>(InStaticClass, TEXT("Prev"), &HStringPropertyTest::Prev);
	HStructBuilder::AddProperty<HStringPropertyTest, HString, HStringProperty>(InStaticClass, TEXT("StringProperty"), &HStringPropertyTest::StringProperty);
	HStructBuilder::AddProperty<HStringPropertyTest, HChar, HCharacterProperty>(InStaticClass, TEXT("Post"), &HStringPropertyTest::Post);
}


IMPLEMENT_CLASS(HStringPropertyTest);

void HInheritanceTest::__Fill_Class_Property_HInheritanceTest(HClass* InStaticClass)
{
	HStructBuilder::AddProperty<HInheritanceTest, int16, HNumericProperty>(InStaticClass, TEXT("InheritanceProperty"), &HInheritanceTest::InheritanceProperty);
	HStructBuilder::SetSuper<HReflectionTest>(InStaticClass);
}


IMPLEMENT_CLASS(HInheritanceTest);

void HObjectInheritedTest::__Fill_Class_Property_HObjectInheritedTest(HClass* InStaticClass)
{
	HStructBuilder::SetSuper<HObjectBase>(InStaticClass);
}


IMPLEMENT_CLASS(HObjectInheritedTest);

void HFunctionTestObject::__Fill_Class_Property_HFunctionTestObject(HClass* InStaticClass)
{
	HStructBuilder::AddNativeFunction((HClass*)InStaticClass, &HFunctionTestObject::execAdd, TEXT("Add"));
}

DEFINE_FUNCTION(HFunctionTestObject::execAdd)
{
	HFUNC_GET_FROM_FRAME(int32, HFunc_Param_B);
	HFUNC_GET_FROM_FRAME(int32, HFunc_Param_A);
	*HFUNC_RESULT_PARAM = (void*)HFUNC_THIS->Add(HFunc_Param_A, HFunc_Param_B);
}

IMPLEMENT_CLASS(HFunctionTestObject);
