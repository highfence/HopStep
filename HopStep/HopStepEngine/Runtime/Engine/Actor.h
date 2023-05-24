#pragma once
#include "Core/CoreExport.h"
#include "CoreObject/CoreObjectExport.h"
#include "CoreObject/Reflection/ReflectionMacro.h"

#include "Intermediate/Actor.generated.h"

namespace HopStep
{
	/**
	 * AActor�� �𸮾� �������� ���� �⺻�� �Ǵ� ���� ������Ʈ Ŭ���� �� �ϳ��Դϴ�. AActor�� ��� ���� ������Ʈ�� �⺻ Ŭ������ UObject�� ��ӹ޽��ϴ�.
	 * AActor�� ���� ���迡�� ǥ�õǴ� ��� ��ü�� ��Ÿ����, �׷��� ���, �浹ü, ���� �ùķ��̼� ���� �����մϴ�. ���� ���, ĳ����, ������, ����, Ż��, Ʈ��, �ǹ� �� ��� ���� ������Ʈ�� AActor�� ��ӹ޾� �����˴ϴ�.
	 * AActor�� ���ӿ��� ǥ�õǴ� ��ġ�� ȸ��, �浹 ó��, ���� �ùķ��̼�, �ִϸ��̼�, ����Ʈ��, ��ƼŬ, ī�޶� �ý��� ���� �ٷ� �� �ֽ��ϴ�. AActor�� ���� �������Ʈ�� ���� ���־� ��ũ���� �ý��۰� C++ �ڵ�� ���� ���α׷��� �� ����Ͽ� �ۼ��� �� �ֽ��ϴ�.
	 * ����, AActor�� �𸮾� �������� ���� �߿��� �⺻ Ŭ���� �� �ϳ��̸�, ��� ���� ������Ʈ�� AActor�� ��ӹ޾� �����˴ϴ�. AActor�� ���ӿ��� ǥ�õǴ� ��ġ, ȸ��, �浹 ó��, ���� �ùķ��̼� �� �پ��� ����� �����ϸ�, ���� ���߿� �ſ� �߿��� ������ �մϴ�.
	 */
	HCLASS();
	class HActor : public HObject
	{
		DECLARE_CLASS_BODY(HActor);

	public:

		// AActor�� ��ġ�� ��ȯ�մϴ�.
		HFUNCTION();
		HVector GetLocation() const;

		// AActor�� ��ġ�� �����մϴ�.
		HFUNCTION();
		bool SetLocation(const HVector& NewLocation);

		// AActor�� ȸ���� ��ȯ�մϴ�.
		HFUNCTION();
		HRotator GetRotation() const;

		// AActor�� ȸ���� �����մϴ�.
		HFUNCTION();
		void SetRotation(const HRotator& NewRotation);

		// AActor�� �������� ��ȯ�մϴ�.
		HFUNCTION();
		HVector GetScale() const;

		// AActor�� �������� �����մϴ�.
		HFUNCTION();
		void SetScale(const HVector& NewScale);

		// AActor�� ��ġ, ȸ��, �������� �����մϴ�.
		HFUNCTION();
		void SetTransform(const HTransform& NewTransform);

		// AActor�� ��ġ, ȸ��, �������� ��ȯ�մϴ�.
		HFUNCTION();
		HTransform GetTransform() const;

		// AActor�� ���� ��ġ�� ��ȯ�մϴ�.
		HFUNCTION();
		HVector GetActorLocation() const;
		
		// AActor�� ���� ��ġ�� �����մϴ�.
		HFUNCTION();
		void SetActorLocation(const HVector& NewLocation);

		// AActor�� ���� ȸ���� ��ȯ�մϴ�.
		HFUNCTION();
		HRotator GetActorRotation() const;

		// AActor�� ���� ȸ���� �����մϴ�.
		HFUNCTION();
		void SetActorRotation(const HRotator& NewRotation);

		// AActor�� ���� �������� ��ȯ�մϴ�.
		HFUNCTION();
		HVector GetActorScale() const;

		// AActor�� ���� �������� �����մϴ�.
		HFUNCTION();
		void SetActorScale(const HVector& NewScale);

		// AActor�� ���� ��ġ, ȸ��, �������� �����մϴ�.
		HFUNCTION();
		void SetActorTransform(const HTransform& NewTransform);

		// AActor�� ���� ��ġ, ȸ��, �������� ��ȯ�մϴ�.
		HFUNCTION();
		HTransform GetActorTransform() const;

		// AActor�� ��Ʈ ������Ʈ�� ��ȯ�մϴ�.
		HFUNCTION();
		class HSceneComponent* GetRootComponent() const;

		HFUNCTION();
		HQuat GetActorQuat() const;

	protected:

		HPROPERTY();
		class HSceneComponent* RootComponent = nullptr;
	};
}