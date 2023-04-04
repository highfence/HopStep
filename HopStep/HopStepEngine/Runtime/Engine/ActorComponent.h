#pragma once
#include "CoreObject/CoreObjectExport.h"
#include "Intermediate/ActorComponent.generated.h"

namespace HopStep
{
	/**
	 * ���Ϳ� �����Ǵ� ���� ����Դϴ�. ���ʹ� ���� ������ ��ü�� ��Ÿ����, ActorComponent�� ����Ͽ� ������ ������ ������ �� �ֽ��ϴ�. ���� ���, ������ �̵�, ȸ��, ü��, ���� ���� ������ �� �ֽ��ϴ�.
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