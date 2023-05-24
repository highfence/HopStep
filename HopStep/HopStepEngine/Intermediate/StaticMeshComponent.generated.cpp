#include "HopStep.h"
#include "Runtime\Engine\StaticMeshComponent.h"

using namespace HopStep;

void HStaticMeshComponent::__Fill_Class_Property_HStaticMeshComponent(HClass* InStaticClass)
{
	HStructBuilder::SetSuper<HMeshComponent>(InStaticClass);
}

IMPLEMENT_CLASS(HStaticMeshComponent);
