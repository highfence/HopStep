#pragma once
#include "Core\PrimitiveTypeDefines.h"
#include "Core\HopStepOverrides.h"
#include "..\Object\GCInterface.h"
#include "Property.h"
#include "PrimitiveProperty.h"
#include "Struct.h"
#include "ReflectionConcepts.h"
#include "Function.h"

namespace HopStep
{
	template <class TClass, class TField>
	int32 GetOffsetOf(TField TClass::* InClassField)
	{
		return (int32)((int8*)&((TClass*)nullptr->*InClassField) - (int8*)nullptr);
	}

	struct HStructBuilder
	{
		template <class TStructType, class TFieldType, class TPropertyType> requires HPropertyDerived<TPropertyType>
		static void AddProperty(HStruct* InStruct, const HString& InFieldName, TFieldType TStructType::*InField);

		template <class TFieldType, class TPropertyType>
		static void IntializePropertyFlags(HProperty* Property);

		template <class TSuperType> requires StaticClassGetable<TSuperType>
		static void SetSuper(HStruct* InStruct);

		static void AddNativeFunction(class HClass* InOwnerStruct, HNativeFuncPtr FuncPtr, HString FunctionName);
	};

	template<class TStructType, class TFieldType, class TPropertyType> requires HPropertyDerived<TPropertyType>
	inline void HStructBuilder::AddProperty(HStruct* InStruct, const HString& InFieldName, TFieldType TStructType::* InField)
	{
		int32 PropertyOffset = GetOffsetOf<TStructType, TFieldType>(InField);
		int32 FieldSize = sizeof(TFieldType);
		HString PropertyName = InFieldName;

		TUniquePtr<HProperty> NewProperty = std::make_unique<TPropertyType>(PropertyName, PropertyOffset, FieldSize);
		IntializePropertyFlags<TFieldType, TPropertyType>(NewProperty.get());
		InStruct->Properties.push_back(std::move(NewProperty));
	}

	template<class TFieldType, class TPropertyType>
	inline void HStructBuilder::IntializePropertyFlags(HProperty* Property)
	{
		using TPureFieldType = std::remove_pointer<TFieldType>::type;

		if constexpr (std::is_integral_v<TPureFieldType>)
		{
			Property->SetPropertyFlag(EPropertyFlag::IntProperty);
		}
		else if constexpr (std::is_floating_point_v<TPureFieldType>)
		{
			Property->SetPropertyFlag(EPropertyFlag::FloatProperty);
		}
		if constexpr (std::is_unsigned_v<TPureFieldType>)
		{
			Property->SetPropertyFlag(EPropertyFlag::UnsignedProperty);
		}
		if constexpr (std::is_class_v<TPureFieldType>)
		{
			Property->SetPropertyFlag(EPropertyFlag::ClassProperty);
			Property->TypeFlag |= static_cast<uint64>(HField::HTypeFlag::Class);
		}
		if constexpr (std::is_same_v<HArrayProperty, TPropertyType>)
		{
			Property->SetPropertyFlag(EPropertyFlag::ArrayProperty);
			Property->TypeFlag |= static_cast<uint64>(HField::HTypeFlag::Container);
		}

		if constexpr (std::derived_from<TPureFieldType, IGCObject>)
		{
			Property->TypeFlag |= static_cast<uint64>(HField::HTypeFlag::GarbageCollectable);
		}

		if (Property->IsClassType() == false && Property->IsContainerType() == false)
		{
			Property->TypeFlag |= static_cast<uint64>(HField::HTypeFlag::Primitive);
		}
	}

	template<class TSuperType> requires StaticClassGetable<TSuperType>
	inline void HStructBuilder::SetSuper(HStruct* InStruct)
	{
		InStruct->Super = TSuperType::StaticClass();
	}
}
