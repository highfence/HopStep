#include "..\HopStep.h"
#include "ReflectionTest.generated.h"
#include "../CoreObject/Reflection/ReflectionTest.h"

using namespace HopStep::CoreObject::Reflection;

void HReflectionTest::__Fill_Class_Property_HReflectionTest(HClass* InStaticClass)
{
	HStructBuilder::AddProperty<HReflectionTest, int32>(InStaticClass, TEXT("A"), &HReflectionTest::A);
	HStructBuilder::AddProperty<HReflectionTest, int32>(InStaticClass, TEXT("B"), &HReflectionTest::B);
	HStructBuilder::AddProperty<HReflectionTest, int32>(InStaticClass, TEXT("C"), &HReflectionTest::C);
}
IMPLEMENT_CLASS(HReflectionTest);
