#pragma once
#include "..\..\Core\CoreExport.h"
#include "..\Reflection\ReflectionConcepts.h"
#include "..\Reflection\ReflectionMacro.h"
#include "..\Reflection\Class.h"
#include "..\..\Intermediate\ObjectBase.generated.h"

/**
 * Type register interface.
 */
struct IStaticTypeRegister
{
	virtual HClass* GetClass() abstract;
};

/**
 *  
 */
template <StaticClassGetable TClass>
struct HStaticClassRegister : public IStaticTypeRegister
{
	HStaticClassRegister();

	HClass* GetClass()
	{
		return TClass::StaticClass();
	}
};

/**
 *  
 */
static HopStep::TArray<IStaticTypeRegister*>& GetStaticTypeRegisterArray()
{
	static HopStep::TArray<IStaticTypeRegister*> StaticTypeRegisters;
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
	bool IsA() const
	{
		const HClass* ThatClass = TClass::StaticClass();
		const HClass* ThisClass = GetClass();

		return ThisClass->IsChildOf(ThatClass);
	}

	HClass* GetClass() const { return ClassPrivate; }
	// Todo: Remove this.
	void SetClass(HClass* InClass) 
	{
		Name = InClass->GetName();
		ClassPrivate = InClass; 
	}

private:

	HString Name;
	HClass* ClassPrivate = nullptr;
};

