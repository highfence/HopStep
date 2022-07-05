#include "..\HopStep.h"
#include "ReflectionTest.generated.h"
#include "..\ReflectionObjectTest.h"

using namespace HopStep::CoreObject::Reflection;

void HReflectionObjectTest::__Fill_Class_Property_HReflectionObjectTest(HClass* InStaticClass)
{
	HStructBuilder::AddProperty<HReflectionObjectTest, int32>(InStaticClass, TEXT("A"), &HReflectionObjectTest::A);
	HStructBuilder::AddProperty<HReflectionObjectTest, int32>(InStaticClass, TEXT("B"), &HReflectionObjectTest::B);
	HStructBuilder::AddProperty<HReflectionObjectTest, int32>(InStaticClass, TEXT("C"), &HReflectionObjectTest::C);
}
IMPLEMENT_CLASS(HReflectionObjectTest);
