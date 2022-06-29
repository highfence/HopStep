#include "HopStep.h"
#include "Property.h"
#include "Struct.h"

namespace HopStep::CoreObject::Reflection
{
	HStruct* HStruct::GetSuper() const
	{
		return Super;
	}

	const HArray<HProperty*> HStruct::GetProperties(bool bIncludeSuper /*= true*/)
	{
		HArray<HProperty*> Result;
		if (bIncludeSuper)
		{
			for (HStruct* SuperIter = Super; SuperIter; SuperIter = SuperIter->Super)
			{
				Result.reserve(Super->Properties.size());
				Result.insert(Result.end(), Super->Properties.begin(), Super->Properties.end());
			}
		}

		Result.reserve(Properties.size());
		Result.insert(Result.end(), Properties.begin(), Properties.end());
		return Result;
	}

	void HStruct::AddProperty(HUniquePtr<HProperty>& InProperty)
	{
		Properties.emplace_back(std::move(InProperty));
	}
}
