#include "HopStep.h"
#include "CoreObject\Object\Object.h"

using namespace HopStep;

void HObject::__Fill_Class_Property_HObject(HClass* InStaticClass)
{
	HStructBuilder::SetSuper<HObjectBase>(InStaticClass);
}

IMPLEMENT_CLASS(HObject);
