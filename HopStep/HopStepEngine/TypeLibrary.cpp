#include "HopStep.h"
#include "TypeLibrary.h"


namespace HopStep::CoreObject::Reflection
{
	HTypeLibrary::~HTypeLibrary()
	{
		Types.clear();
	}

	HTypeLibrary* HTypeLibrary::Get()
	{
		static HTypeLibrary Library;
		return &Library;
	}

	std::vector<class HType*> HTypeLibrary::GetTypes()
	{
		return Types;
	}

	void HTypeLibrary::RegisterNewType(HType* InType)
	{
		if (InType == nullptr) return;

		Types.emplace_back(InType);
	}
}
	

