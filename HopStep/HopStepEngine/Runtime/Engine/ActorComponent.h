#pragma once
#include "CoreObject/CoreObjectExport.h"
#include "Intermediate/ActorComponent.generated.h"

namespace HopStep
{
	/**
	 * 액터에 부착되는 구성 요소입니다. 액터는 게임 내에서 개체를 나타내며, ActorComponent를 사용하여 액터의 동작을 정의할 수 있습니다. 예를 들어, 액터의 이동, 회전, 체력, 무기 등을 구현할 수 있습니다.
	 */
	HCLASS();
	class HActorComponent : public HObject
	{
		DECLARE_CLASS_BODY(HActorComponent);

	public:

		HActorComponent();
		virtual ~HActorComponent();

	};
}