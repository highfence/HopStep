#pragma once
#include "Struct.h"
#include "Property.h"
#include "PrimitiveProperty.h"
#include "..\..\Core\PrimitiveTypeDefines.h"
#include "..\..\Core\HopStepOverrides.h"

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
		HString PropertyName = InFieldName;

		HUniquePtr<HProperty> NewProperty = std::make_unique<HProperty>(PropertyName, PropertyOffset, FieldSize);
		InStruct->Properties.push_back(std::move(NewProperty));
	}
}
