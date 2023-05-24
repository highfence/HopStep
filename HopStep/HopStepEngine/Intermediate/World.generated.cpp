#include "HopStep.h"
#include "Runtime\Engine\World.h"

using namespace HopStep;

void HWorld::__Fill_Class_Property_HWorld(HClass* InStaticClass)
{
	HStructBuilder::AddProperty<HWorld, HLevel, HClassProperty>(InStaticClass, TEXT("PersistentLevel"), &HWorld::PersistentLevel);
	HStructBuilder::SetSuper<HObject>(InStaticClass);
}

IMPLEMENT_CLASS(HWorld);
