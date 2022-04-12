#include "HopStep.h"
#include "Property.h"
#include "Type.h"

namespace HopStep::CoreObject::Reflection
{
	size_t HType::GetSize() const
	{
		return Size;
	}

	HType* HType::GetSuper() const
	{
		return Super;
	}

	const std::vector<HProperty*> HType::GetProperties(bool bIncludeSuper /*= true*/)
	{
		std::vector<HProperty*> Result;
		if (bIncludeSuper)
		{
			for (HType* SuperIter = Super; SuperIter; SuperIter = SuperIter->Super)
			{
				Result.reserve(Super->Properties.size());
				Result.insert(Result.end(), Super->Properties.begin(), Super->Properties.end());
			}
		}

		Result.reserve(Properties.size());
		Result.insert(Result.end(), Properties.begin(), Properties.end());
		return Result;
	}

	void HType::RegisterToMetaData()
	{
		auto* Library = HMetadataLibrary::Get();
		Library->RegisterNewType(this);
	}

}
