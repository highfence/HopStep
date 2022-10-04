#include "HopStep.h"
#include "Object.generated.h"
#include "CoreObject\Object\Object.h"

using namespace HopStep::CoreObject::Reflection;

void HObject::__Fill_Class_Property_HObject(HClass* InStaticClass)
{
	HStructBuilder::AddProperty<HObject, int32>(InStaticClass, TEXT("a"), &HObject::a);
}
IMPLEMENT_CLASS(HObject);
