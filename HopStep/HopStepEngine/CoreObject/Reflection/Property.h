#pragma once
#include "..\..\Core\PrimitiveTypeDefines.h"
#include "..\..\Core\HopStepOverrides.h"
#include "Type.h"

namespace HopStep
{
	enum class EPropertyFlag : uint64
	{
		IntProperty = (0x01 << 0),
		FloatProperty = (0x01 << 1),
		UnsignedProperty = (0x01 << 2),
		ClassProperty = (0x01 << 3),
		ArrayProperty = (0x01 << 4)
	};

	class HProperty : public HType
	{
	public:

		HProperty(const HString& InName, int32 InOffset, int32 InElementSize, int32 InArrayDimension = 1);

		virtual ~HProperty();

		virtual void ExportToString(HString& TextOutput, void const* ObjectPtr) const = 0;

		template <class TValueType>
		TValueType* GetPtr(void const* ObjectPtr) const;

		template <class TValueType>
		TValueType Get(void const* ObjectPtr) const;

		template <class TValueType>
		void SetValue(void const* ObjectPtr, TValueType Value) const;

		void SetPropertyFlag(EPropertyFlag Flag);
		bool GetPropertyFlag(EPropertyFlag Flag) const;

	protected:

		int32 Offset;
		int32 ElementSize;
		int32 TotalSize;
		int32 ArrayDimension;
		uint64 PropertyFlags;
	};

	template<class TValueType>
	inline TValueType* HProperty::GetPtr(void const* ObjectPtr) const
	{
		return (TValueType*)((char*)ObjectPtr + Offset);
	}

	template<class TValueType>
	inline TValueType HProperty::Get(void const* ObjectPtr) const
	{
		return (TValueType)((char*)ObjectPtr + Offset);
	}

	template<class TValueType>
	inline void HProperty::SetValue(void const* ObjectPtr, TValueType Value) const
	{
		TValueType* Ptr = GetPtr<TValueType>(ObjectPtr);
		*Ptr = Value;
	}
}
