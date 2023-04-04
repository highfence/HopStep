#include "HopStep.h"
#include "SceneComponent.generated.h"
#include "Runtime\Engine\SceneComponent.h"

using namespace HopStep;

void HSceneComponent::__Fill_Class_Property_HSceneComponent(HClass* InStaticClass)
{
	HStructBuilder::SetSuper<HActorComponent>(InStaticClass);
}

IMPLEMENT_CLASS(HSceneComponent);
