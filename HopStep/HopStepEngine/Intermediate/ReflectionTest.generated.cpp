#include "HopStep.h"
#include "ReflectionTest.generated.h"
#include "CoreObject\Reflection\ReflectionTest.h"
#include "CoreObject\Reflection\ReflectionTest.h"

using namespace HopStep::CoreObject::Reflection;

void HInnerClassTest::__Fill_Class_Property_HInnerClassTest(HClass* InStaticClass)
{
	HStructBuilder::AddProperty<HInnerClassTest, int32, HNumericProperty>(InStaticClass, TEXT("InnerA"), &HInnerClassTest::InnerA);
	HStructBuilder::AddProperty<HInnerClassTest, int8, HNumericProperty>(InStaticClass, TEXT("InnerB"), &HInnerClassTest::InnerB);
}
IMPLEMENT_CLASS(HInnerClassTest);

void HReflectionTest::__Fill_Class_Property_HReflectionTest(HClass* InStaticClass)
{
	HStructBuilder::AddProperty<HReflectionTest, int32, HNumericProperty>(InStaticClass, TEXT("A"), &HReflectionTest::A);
	HStructBuilder::AddProperty<HReflectionTest, int32, HNumericProperty>(InStaticClass, TEXT("B"), &HReflectionTest::B);
	HStructBuilder::AddProperty<HReflectionTest, bool, HBooleanProperty>(InStaticClass, TEXT("C"), &HReflectionTest::C);
	HStructBuilder::AddProperty<HReflectionTest, int32, HNumericProperty>(InStaticClass, TEXT("D"), &HReflectionTest::D);
	HStructBuilder::AddProperty<HReflectionTest, HInnerClassTest*, HClassProperty>(InStaticClass, TEXT("InnerClassPtr"), &HReflectionTest::InnerClassPtr);
}
IMPLEMENT_CLASS(HReflectionTest);
