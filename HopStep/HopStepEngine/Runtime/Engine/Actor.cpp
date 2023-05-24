#include "Actor.h"
#include "Core\Math\Transform.h"
#include "SceneComponent.h"

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

	HVector HActor::GetLocation() const
	{
		return RootComponent ? RootComponent->GetComponentLocation() : HVector::ZeroVector;
	}

	bool HActor::SetLocation(const HVector& NewLocation)
	{
		if (RootComponent)
		{
			const HVector Delta = NewLocation - RootComponent->GetComponentLocation();
			return RootComponent->MoveComponent(Delta, GetActorQuat());
		}

		return false;
	}

	HRotator HActor::GetRotation() const
	{
		return HRotator();
	}

	void HActor::SetRotation(const HRotator& NewRotation)
	{
	}

	HVector HActor::GetScale() const
	{
		return HVector();
	}

	void HActor::SetScale(const HVector& NewScale)
	{
	}

	void HActor::SetTransform(const HTransform& NewTransform)
	{
	}

	HTransform HActor::GetTransform() const
	{
		return HTransform();
	}

	HVector HActor::GetActorLocation() const
	{
		return HVector();
	}

	void HActor::SetActorLocation(const HVector& NewLocation)
	{
	}

	HRotator HActor::GetActorRotation() const
	{
		return HRotator();
	}

	void HActor::SetActorRotation(const HRotator& NewRotation)
	{
	}

	HVector HActor::GetActorScale() const
	{
		return HVector();
	}

	void HActor::SetActorScale(const HVector& NewScale)
	{
	}

	void HActor::SetActorTransform(const HTransform& NewTransform)
	{
	}

	HQuat HActor::GetActorQuat() const
	{
		return HQuat();
	}
}