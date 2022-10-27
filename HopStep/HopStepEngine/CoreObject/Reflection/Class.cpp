#include "Class.h"

namespace HopStep::CoreObject::Reflection
{
	const HFunction* HClass::FindFunction(const HString& FunctionName) const
	{
		auto AllFunctions = GetFunctions();

		auto FindPtr = std::find_if(AllFunctions.begin(), AllFunctions.end(), [FunctionName](const HFunction* FuncPtr) -> bool 
			{
				return FuncPtr->GetName() == FunctionName;
			});

		if (FindPtr == AllFunctions.end()) return nullptr;

		const HFunction* FuncPtr = (*FindPtr);

		return FuncPtr;
	}

	const HArray<HFunction*> HClass::GetFunctions() const
	{
		HArray<HFunction*> Result;

		for (int32 Index = 0; Index < Functions.size(); ++Index)
		{
			HFunction* Func = Functions[Index].get();
			Result.push_back(Func);
		}

		return Result;
	}
}
