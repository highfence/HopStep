#include "HopStep.h"
#include "Runtime\Engine\MeshComponent.h"

using namespace HopStep;

void HMeshComponent::__Fill_Class_Property_HMeshComponent(HClass* InStaticClass)
{
	HStructBuilder::SetSuper<HPrimitiveComponent>(InStaticClass);
}

IMPLEMENT_CLASS(HMeshComponent);
