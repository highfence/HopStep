#pragma once
#include "Field.h"
#include "..\..\Core\CoreExport.h"

namespace HopStep
{
	enum class EPropertyFlag : uint64
	{
		// Numeric Property Flags
		IntProperty = (0x01 << 0),
		FloatProperty = (0x01 << 1),
		UnsignedProperty = (0x01 << 2),
	};

	class HProperty : public HField
	{
	public:

		explicit HProperty(const HString& InName, int32 InOffset, int32 InElementSize, int32 InArrayDimension = 1)
			: HField(InName), Offset(InOffset), ElementSize(InElementSize), ArrayDimension(InArrayDimension), PropertyFlags(0u)
		{
			TotalSize = ElementSize * ArrayDimension;
		}

		virtual ~HProperty() {}

		virtual void ExportToString(HString& TextOutput, void const* ObjectPtr) const abstract;

		template <class TValueType>
		TValueType* GetPtr(void const* ObjectPtr) const;

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
		// Todo : Can offsetof(TClass, InClassField) replace this value?
		return (int32)((int8*)&((TClass*)nullptr->*InClassField) - (int8*)nullptr);
	}

	template<class TValueType>
	inline TValueType* HProperty::GetPtr(void const* ObjectPtr) const
	{
		return (TValueType*)((char*)ObjectPtr + Offset);
	}
}
