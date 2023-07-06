#pragma once
#include "Core/CoreExport.h"
#include "ActorComponent.h"
#include "Intermediate/SceneComponent.generated.h"

namespace HopStep
{
	/*
	 * ��ġ, ȸ��, ũ�� ���� ��ȯ�� ��Ÿ���� �⺻ Ŭ�����Դϴ�. ��� ������Ʈ�� SceneComponent�� ��ӹ޽��ϴ�. SceneComponent�� ���Ϳ� �Բ� ���Ǹ�, ���͸� �����̰ų� ȸ����Ű�� ���� ��ȯ �۾��� ���� ������ �� �ֽ��ϴ�.
	 */
	HCLASS();
	class HSceneComponent : public HActorComponent
	{
		DECLARE_CLASS_BODY(HSceneComponent)

	public:

		HSceneComponent();
		virtual ~HSceneComponent();

		const HTransform& GetComponentTransform() const 
		{
			return ComponentToWorld; 
		}

		HVector GetComponentLocation() const
		{
			return ComponentToWorld.GetLocation(); 
		}

		bool MoveComponent(const HVector& Delta, const HQuat& NewRotation);

	private:

		HTransform ComponentToWorld;

		TArray<HSceneComponent*> AttachChildren;
	};
}