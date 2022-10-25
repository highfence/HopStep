#include "HopStep.h"
#include "StructBuilder.h"

namespace HopStep::CoreObject::Reflection
{
	void HStructBuilder::AddNativeFunctionProperty(HStruct* InOwnerStruct, HNativeFuncPtr FuncPtr, HString FunctionName)
	{
		HUniquePtr<HProperty> NewProperty = std::make_unique<HNativeFunction>(FunctionName, InOwnerStruct, FuncPtr);

		IntializePropertyFlags<HNativeFunction>(NewProperty.get());
		InStruct->Properties.push_back(std::move(NewProperty));
	}
}
