#include <vector>
#include "TypeLibrary.h"


namespace HopStep
{
	HTypeLibrary::~HTypeLibrary()
	{
		Types.clear();
	}

	HTypeLibrary* HTypeLibrary::GetPropertyPtr()
	{
		static HTypeLibrary Library;
		return &Library;
	}

	std::vector<class HField*> HTypeLibrary::GetTypes()
	{
		return Types;
	}

	void HTypeLibrary::RegisterNewType(HField* InType)
	{
		if (InType == nullptr) return;

		Types.emplace_back(InType);
	}
}
	

