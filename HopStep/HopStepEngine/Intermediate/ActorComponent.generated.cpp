#include "HopStep.h"
#include "ActorComponent.generated.h"
#include "Runtime\Engine\ActorComponent.h"

using namespace HopStep;

void HActorComponent::__Fill_Class_Property_HActorComponent(HClass* InStaticClass)
{
	HStructBuilder::SetSuper<HObject>(InStaticClass);
}

IMPLEMENT_CLASS(HActorComponent);
