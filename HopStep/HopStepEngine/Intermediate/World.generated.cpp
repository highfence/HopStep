#include "HopStep.h"
#include "World.generated.h"
#include "Runtime\Engine\World.h"

using namespace HopStep;

void HWorld::__Fill_Class_Property_HWorld(HClass* InStaticClass)
{
	HStructBuilder::AddProperty<HWorld, TObjectPtr<class, HClassProperty>(InStaticClass, TEXT("HLevel>"), &HWorld::HLevel>);
	HStructBuilder::SetSuper<HObject>(InStaticClass);
}

IMPLEMENT_CLASS(HWorld);
