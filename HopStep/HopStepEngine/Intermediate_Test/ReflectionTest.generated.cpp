#include ReflectionTest.generated.h

IMPLEMENT_CLASS(HReflectionObjectTest);
void __Fill_Class_Property_HReflectionObjectTest(HopStep::CoreObject::Reflection::HClass* InStaticClass)
{
	HStructBuilder::AddProperty<HReflectionObjectTest, int32>(InStaticClass, "A", &HReflectionObjectTest::A);
	HStructBuilder::AddProperty<HReflectionObjectTest, int32>(InStaticClass, "B", &HReflectionObjectTest::B);
	HStructBuilder::AddProperty<HReflectionObjectTest, int32>(InStaticClass, "C", &HReflectionObjectTest::C);
}
