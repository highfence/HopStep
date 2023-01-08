#include "Core/HopStepOverrides.h"
#include "Core/PrimitiveTypeDefines.h"
#include "Struct.h"

namespace HopStep
{
	HStruct::HStruct(const HString& InName)
		: HType(InName)
	{
		Properties.clear();
	}

	HStruct::~HStruct()
	{
		Properties.clear();
	}

	HStruct* HStruct::GetSuper() const
	{
		return Super;
	}

	const TArray<HProperty*> HStruct::GetProperties(bool bIncludeSuper /*= true*/)
	{
		TArray<HProperty*> Result;

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
		const TArray<HProperty*> AllProperties = GetProperties();

		auto FindingPropertyIter = std::find_if(AllProperties.begin(), AllProperties.end(), [PropertyName](const HProperty* InProperty) -> bool 
			{
				return InProperty->GetName().ToString() == PropertyName;
			});

		if (FindingPropertyIter == AllProperties.end()) return nullptr;

		const HProperty* PropertyPtr = (*FindingPropertyIter);

		return PropertyPtr;
	}

	bool HStruct::IsChildOf(const HStruct* OtherClass) const
	{
		const HStruct* CheckPtr = this;

		while (CheckPtr)
		{
			if (CheckPtr == OtherClass)
			{
				return true;
			}

			CheckPtr = CheckPtr->Super;
		}

		return false;
	}
}
