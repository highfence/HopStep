#include "FieldClass.h"
#include "Field.h"

namespace HopStep
{
	HField* HFieldClass::ConstructDefaultObject()
	{
		return nullptr;
	}

	HFieldClass::HFieldClass(const HChar* InName, uint64 InId, uint64 InCastFlags, HFieldClass* InSuperClass, HField* (*ConstructFnPtr)(const HName&))
		: Name(InName), Id(InId), CastFlags(InCastFlags), SuperClass(InSuperClass), ConstructFn(ConstructFnPtr), DefaultObject(nullptr)
	{
		GetAllFieldClasses().push_back(this);
		GetNameFieldClassMap().insert(std::make_pair(Name, this));
	}

	HFieldClass::~HFieldClass()
	{
		delete DefaultObject;
		DefaultObject = nullptr;
	}

	TArray<HFieldClass*>& HFieldClass::GetAllFieldClasses()
	{
		static TArray<HFieldClass*> AllClasses;
		return AllClasses;
	}

	TMap<HName, HFieldClass*>& HFieldClass::GetNameFieldClassMap()
	{
		static TMap<HName, HFieldClass*> NameFieldClassMap;
		return NameFieldClassMap;
	}
}