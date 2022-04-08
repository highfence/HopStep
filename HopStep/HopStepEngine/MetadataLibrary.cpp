#include "HopStep.h"
#include "MetadataLibrary.h"

HMetadataLibrary Library;

HMetadataLibrary& HMetadataLibrary::Get()
{
	return Library;
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
	

