#pragma once
#include "Core/CoreExport.h"
#include "CoreObject/CoreObjectExport.h"
#include "CoreObject/Reflection/ReflectionMacro.h"

#include "Intermediate/Actor.generated.h"

namespace HopStep
{
	/**
	 * AActor는 언리얼 엔진에서 가장 기본이 되는 게임 오브젝트 클래스 중 하나입니다. AActor는 모든 게임 오브젝트의 기본 클래스인 UObject를 상속받습니다.
	 * AActor는 게임 세계에서 표시되는 모든 물체를 나타내며, 그래픽 요소, 충돌체, 물리 시뮬레이션 등을 제공합니다. 예를 들어, 캐릭터, 아이템, 무기, 탈것, 트리, 건물 등 모든 게임 오브젝트는 AActor를 상속받아 구현됩니다.
	 * AActor는 게임에서 표시되는 위치와 회전, 충돌 처리, 물리 시뮬레이션, 애니메이션, 라이트맵, 파티클, 카메라 시스템 등을 다룰 수 있습니다. AActor는 또한 블루프린트와 같은 비주얼 스크립팅 시스템과 C++ 코드와 같은 프로그래밍 언어를 사용하여 작성될 수 있습니다.
	 * 따라서, AActor는 언리얼 엔진에서 가장 중요한 기본 클래스 중 하나이며, 모든 게임 오브젝트가 AActor를 상속받아 구현됩니다. AActor는 게임에서 표시되는 위치, 회전, 충돌 처리, 물리 시뮬레이션 등 다양한 기능을 제공하며, 게임 개발에 매우 중요한 역할을 합니다.
	 */
	HCLASS();
	class HActor : public HObject
	{
		DECLARE_CLASS_BODY(HActor);

	public:

		// AActor의 위치를 반환합니다.
		HFUNCTION();
		HVector GetLocation() const;

		// AActor의 위치를 설정합니다.
		HFUNCTION();
		bool SetLocation(const HVector& NewLocation);

		// AActor의 회전을 반환합니다.
		HFUNCTION();
		HRotator GetRotation() const;

		// AActor의 회전을 설정합니다.
		HFUNCTION();
		void SetRotation(const HRotator& NewRotation);

		// AActor의 스케일을 반환합니다.
		HFUNCTION();
		HVector GetScale() const;

		// AActor의 스케일을 설정합니다.
		HFUNCTION();
		void SetScale(const HVector& NewScale);

		// AActor의 위치, 회전, 스케일을 설정합니다.
		HFUNCTION();
		void SetTransform(const HTransform& NewTransform);

		// AActor의 위치, 회전, 스케일을 반환합니다.
		HFUNCTION();
		HTransform GetTransform() const;

		// AActor의 액터 위치를 반환합니다.
		HFUNCTION();
		HVector GetActorLocation() const;
		
		// AActor의 액터 위치를 설정합니다.
		HFUNCTION();
		void SetActorLocation(const HVector& NewLocation);

		// AActor의 액터 회전을 반환합니다.
		HFUNCTION();
		HRotator GetActorRotation() const;

		// AActor의 액터 회전을 설정합니다.
		HFUNCTION();
		void SetActorRotation(const HRotator& NewRotation);

		// AActor의 액터 스케일을 반환합니다.
		HFUNCTION();
		HVector GetActorScale() const;

		// AActor의 액터 스케일을 설정합니다.
		HFUNCTION();
		void SetActorScale(const HVector& NewScale);

		// AActor의 액터 위치, 회전, 스케일을 설정합니다.
		HFUNCTION();
		void SetActorTransform(const HTransform& NewTransform);

		// AActor의 액터 위치, 회전, 스케일을 반환합니다.
		HFUNCTION();
		HTransform GetActorTransform() const;

		// AActor의 루트 컴포넌트를 반환합니다.
		HFUNCTION();
		class HSceneComponent* GetRootComponent() const;

		HFUNCTION();
		HQuat GetActorQuat() const;

	protected:

		HPROPERTY();
		class HSceneComponent* RootComponent = nullptr;
	};
}