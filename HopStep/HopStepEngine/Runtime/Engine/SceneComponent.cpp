#include "SceneComponent.h"

namespace HopStep
{
	HSceneComponent::HSceneComponent()
	{
	}

	HSceneComponent::~HSceneComponent()
	{
	}

	bool HSceneComponent::MoveComponent(const HVector& Delta, const HQuat& NewRotation)
	{
		HVector NewLocation = GetComponentLocation() + Delta;

		ComponentToWorld = HTransform(NewRotation, NewLocation);

		return true;
	}
}
