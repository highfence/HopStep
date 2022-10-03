#include "../../Core/HopStepOverrides.h"
#include "../../Core/PrimitiveTypeDefines.h"
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
				
				for (int32 Index = 0; Index < Super->Properties.size(); ++Index)
				{
					Result.push_back(Super->Properties[Index].get());
				}
			}
		}

		Result.reserve(Properties.size());
		for (int32 Index = 0; Index < Properties.size(); ++Index)
		{
			Result.push_back(Properties[Index].get());
		}

		return Result;
	}

	const HProperty* HStruct::FindProperty(const HString& PropertyName)
	{
		const HArray<HProperty*> AllProperties = GetProperties();

		auto FindingPropertyIter = std::find_if(AllProperties.begin(), AllProperties.end(), [PropertyName](const HProperty* InProperty) -> bool 
			{
				return InProperty->GetName() == PropertyName;
			});

		if (FindingPropertyIter == AllProperties.end()) return nullptr;

		const HProperty* PropertyPtr = (*FindingPropertyIter);

		return PropertyPtr;
	}
}
