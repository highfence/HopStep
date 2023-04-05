#pragma once
#include "Core/CoreExport.h"
#include "ActorComponent.h"
#include "Intermediate/SceneComponent.generated.h"

namespace HopStep
{
	/*
	 * 위치, 회전, 크기 등의 변환을 나타내는 기본 클래스입니다. 모든 오브젝트는 SceneComponent를 상속받습니다. SceneComponent는 액터와 함께 사용되며, 액터를 움직이거나 회전시키는 등의 변환 작업을 쉽게 수행할 수 있습니다.
	 */
	HCLASS();
	class HSceneComponent : public HActorComponent
	{
		DECLARE_CLASS_BODY(HSceneComponent);

	public:

		HSceneComponent();
		virtual ~HSceneComponent();

		const HTransform& GetComponentTransform() const 
		{
			return ComponentToWorld; 
		}

	protected:

		HTransform ComponentToWorld;
};
}