#pragma once
#include "Field.h"
#include "Core\HopStepCore.h"

namespace HopStep::CoreObject::Reflection
{
	enum class EPropertyFlag : uint64
	{
		IntProperty = (0x01 << 0),
		FloatProperty = (0x01 << 1),
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
		TValueType GetValue(void const* ObjectPtr) const;

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
	inline TValueType HProperty::GetValue(void const* ObjectPtr) const
	{
		TValueType Value;
		void* StartOffsetPtr = (void*)((char*)ObjectPtr + Offset);
		memcpy(&Value, StartOffsetPtr, ElementSize);
		return Value;
	}
}
