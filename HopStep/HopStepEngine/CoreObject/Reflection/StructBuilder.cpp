#include "HopStep.h"
#include "Class.h"
#include "StructBuilder.h"

namespace HopStep
{
	void HStructBuilder::AddNativeFunction(HClass* InOwnerClass, HNativeFuncPtr FuncPtr, HString FunctionName)
	{
		HUniquePtr<HFunction> NewProperty = std::make_unique<HNativeFunction>(FunctionName, InOwnerClass, FuncPtr);

		InOwnerClass->Functions.emplace_back(std::move(NewProperty));
	}
}
