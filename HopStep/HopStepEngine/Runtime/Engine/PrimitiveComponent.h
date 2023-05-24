#pragma once
#include "SceneComponent.h"
#include "CoreObject/CoreObjectExport.h"
#include "Intermediate\PrimitiveComponent.generated.h"

namespace HopStep
{
	/**
	 * ���� ������Ʈ�� �ð����� �κ��� ��Ÿ���ϴ�. ���� ���, ĳ������ �𵨸�, ������ �𵨸�, ���� ����, �̻��� ���� ǥ���ϴ� �� ���˴ϴ�. PrimitiveComponent�� �浹 ó���� ���� ��ɵ� �����մϴ�.
	 */
	HCLASS();
	class HPrimitiveComponent : public HSceneComponent
	{
		DECLARE_CLASS_BODY(HPrimitiveComponent)

	public:

		virtual class HPrimitiveSceneProxy* CreateSceneProxy() = 0;
	};

}