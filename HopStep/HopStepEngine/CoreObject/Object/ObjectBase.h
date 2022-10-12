#pragma once
#include "Core\HopStepCore.h"
#include "CoreObject\Reflection\ReflectionConcepts.h"
#include "CoreObject/Reflection/ReflectionMarco.h"

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

};

