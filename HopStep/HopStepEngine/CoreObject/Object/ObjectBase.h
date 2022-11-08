#pragma once
#include "Core\CoreExport.h"
#include "CoreObject\Reflection\ReflectionConcepts.h"
#include "CoreObject/Reflection/ReflectionMacro.h"
#include "Intermediate\ObjectBase.generated.h"

/**
 * Type register interface.
 */
struct IStaticTypeRegister
{
	virtual class HClass* GetClass() abstract;
};

/**
 *  
 */
template <StaticClassGetable TClass>
struct HStaticClassRegister : public IStaticTypeRegister
{
	HStaticClassRegister();

	class HClass* GetClass()
	{
		return TClass::StaticClass();
	}
};

/**
 *  
 */
static HopStep::HArray<IStaticTypeRegister*>& GetStaticTypeRegisterArray()
{
	static HopStep::HArray<IStaticTypeRegister*> StaticTypeRegisters;
	return StaticTypeRegisters;
}

template<StaticClassGetable TClass>
inline HStaticClassRegister<TClass>::HStaticClassRegister()
{
	GetStaticTypeRegisterArray().emplace_back(this);
}

HCLASS();
class HObjectBase
{
	DECLARE_CLASS_BODY(HObjectBase);

public:

	virtual ~HObjectBase() {};

	template <StaticClassGetable TClass>
	[[deprecated("Do not use HObjectBase::IsA<T> now. Implement later after making CDO & GC System.")]]
	bool IsA() const
	{
		const HClass* ThatClass = TClass::StaticClass();
		const HClass* ThisClass = GetClass();

		return ThisClass->IsChildOf(ThatClass);
	}

	[[deprecated("Do not use HObjectBase::GetClass() now. Implement later after making CDO & GC System.")]]
	HClass* GetClass() const { return ClassPrivate; }

private:

	HClass* ClassPrivate = nullptr;
};

