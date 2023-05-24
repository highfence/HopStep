#pragma once
#include "SceneComponent.h"
#include "CoreObject/CoreObjectExport.h"
#include "Intermediate\PrimitiveComponent.generated.h"

namespace HopStep
{
	/**
	 * 게임 오브젝트의 시각적인 부분을 나타냅니다. 예를 들어, 캐릭터의 모델링, 무기의 모델링, 맵의 지형, 미사일 등을 표시하는 데 사용됩니다. PrimitiveComponent는 충돌 처리를 위한 기능도 제공합니다.
	 */
	HCLASS();
	class HPrimitiveComponent : public HSceneComponent
	{
		DECLARE_CLASS_BODY(HPrimitiveComponent)

	public:

		virtual class HPrimitiveSceneProxy* CreateSceneProxy() = 0;
	};

}