#pragma once
#include "Struct.h"
#include "Property.h"
#include "PrimitiveTypeDefines.h"
#include "HopStepOverrides.h"

namespace HopStep::CoreObject::Reflection
{
	struct HStructBuilder
	{
		template <class TStructType, class TFieldType>
		static void AddProperty(HStruct* InStruct, const HString& InFieldName, TFieldType TStructType::*InField);
	};

	template<class TStructType, class TFieldType>
	inline void HStructBuilder::AddProperty(HStruct* InStruct, const HString& InFieldName, TFieldType TStructType::* InField)
	{
		int32 PropertyOffset = GetOffsetOf<TStructType, TFieldType>(InField);
		int32 FieldSize = sizeof(TFieldType);
		HString StructName = InStruct->GetName();

		HUniquePtr<HProperty> NewProperty = std::make_unique<HProperty>(StructName, PropertyOffset, FieldSize);
		InStruct->Properties.push_back(std::move(NewProperty));
	}
}
