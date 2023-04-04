#include "HopStep.h"
#include "PrimitiveComponent.generated.h"
#include "Runtime\Engine\PrimitiveComponent.h"

using namespace HopStep;

void HPrimitiveComponent::__Fill_Class_Property_HPrimitiveComponent(HClass* InStaticClass)
{
	HStructBuilder::SetSuper<HSceneComponent>(InStaticClass);
}

IMPLEMENT_CLASS(HPrimitiveComponent);
