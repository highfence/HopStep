#include "Actor.h"

namespace HopStep
{
	HTransform HActor::GetActorTransform() const
	{
		// Actor To Transform
		return RootComponent ? RootComponent->GetComponentTransform() : HTransform::Identity;
	}

	HSceneComponent* HActor::GetRootComponent() const
	{
		return RootComponent;
	}
}