#include "HopStep.h"
#include "Object.generated.h"
#include "CoreObject\Object\Object.h"

using namespace HopStep;

void HObject::__Fill_Class_Property_HObject(HClass* InStaticClass)
{
	HStructBuilder::AddProperty<HObject, int32, HNumericProperty>(InStaticClass, TEXT("a"), &HObject::a);
	HStructBuilder::SetSuper<HObjectBase>(InStaticClass);
}

IMPLEMENT_CLASS(HObject);
