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
}
