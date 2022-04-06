#include "HopStep.h"
#include "MetadataLibrary.h"

namespace HopStep::Reflection
{
	HMetadataLibrary MetaLibrary;

	HMetadataLibrary& HMetadataLibrary::Get()
	{
		return MetaLibrary;
	}

	std::vector<class HType*> HMetadataLibrary::GetTypes()
	{
		return Types;
	}

	void HMetadataLibrary::RegisterNewType(HType* InType)
	{
		if (InType == nullptr) return;

		Types.emplace_back(InType);
	}
}
