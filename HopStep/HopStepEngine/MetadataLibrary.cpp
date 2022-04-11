#include "HopStep.h"
#include "MetadataLibrary.h"


HMetadataLibrary::~HMetadataLibrary()
{
	Types.clear();
}

HMetadataLibrary* HMetadataLibrary::Get()
{
	static HMetadataLibrary Library;
	return &Library;
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
	

