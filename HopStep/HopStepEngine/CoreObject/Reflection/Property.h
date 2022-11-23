#pragma once
#include "Struct.h"
#include "..\..\Core\CoreExport.h"
#include "..\Object\Object.h"

namespace HopStep
{
	enum class EPropertyFlag : uint64
	{
		IntProperty = (0x01 << 0),
		FloatProperty = (0x01 << 1),
		UnsignedProperty = (0x01 << 2),
		ClassProperty = (0x01 << 3),
		ArrayProperty = (0x01 << 4),
	};

	class HProperty : public HStruct
	{
	public:

		explicit HProperty(const HString& InName, int32 InOffset, int32 InElementSize, int32 InArrayDimension = 1)
			: HStruct(InName), Offset(InOffset), ElementSize(InElementSize), ArrayDimension(InArrayDimension), PropertyFlags(0u)
		{
			TotalSize = ElementSize * ArrayDimension;
		}

		virtual ~HProperty() {}

		virtual void ExportToString(HString& TextOutput, void const* ObjectPtr) const abstract;

		template <class TValueType>
		TValueType* GetPtr(void const* ObjectPtr) const;

		template <class TValueType, class TSelfType>
		TValueType& GetValue(TSelfType&& Self);

		template <class TValueType>
		void SetValue(void const* ObjectPtr, TValueType Value) const
		{
			TValueType* Ptr = GetPtr<TValueType>(ObjectPtr);
			*Ptr = Value;
		}

		void SetPropertyFlag(EPropertyFlag Flag) { PropertyFlags |= static_cast<uint64>(Flag); }
		bool GetPropertyFlag(EPropertyFlag Flag) const { return PropertyFlags & static_cast<uint64>(Flag); }

		int32 Offset;
		int32 ElementSize;
		int32 TotalSize;
		int32 ArrayDimension;
		uint64 PropertyFlags;
	};

	template <class TClass, class TField>
	int32 GetOffsetOf(TField TClass::* InClassField)
	{
		return (int32)((int8*)&((TClass*)nullptr->*InClassField) - (int8*)nullptr);
	}

	template<class TValueType>
	inline TValueType* HProperty::GetPtr(void const* ObjectPtr) const
	{
		return (TValueType*)((char*)ObjectPtr + Offset);
	}

	template<class TValueType, class TSelfType>
	inline TValueType& HProperty::GetValue(TSelfType&& Self)
	{
		using TNonReferenceSelf = TRemoveReference<TSelfType>::Type;

		void* ObjectPtr = nullptr;
		if constexpr (std::is_pointer_v<TNonReferenceSelf> && DerivedFrom<std::remove_pointer_t<TNonReferenceSelf>, HObject>)
		{
			ObjectPtr = reinterpret_cast<void*>(dynamic_cast<HObject*>(Self));
		}
		else
		{
			ObjectPtr = &Self;
		}


	}
}
