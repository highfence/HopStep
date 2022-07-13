#pragma once
#include "Field.h"
#include "..\..\Core\HopStepCore.h"

namespace HopStep::CoreObject::Reflection
{
	class HProperty : public HField
	{
	public:

		explicit HProperty(const HString& InName, int32 InOffset, int32 InElementSize, int32 InArrayDimension = 1)
			: HField(InName), Offset(InOffset), ElementSize(InElementSize), ArrayDimension(InArrayDimension)
		{
			TotalSize = ElementSize * ArrayDimension;
		}

		virtual ~HProperty() {}

		int32 Offset;
		int32 ElementSize;
		int32 TotalSize;
		int32 ArrayDimension;
	};

	template <class TClass, class TField>
	int32 GetOffsetOf(TField TClass::* InClassField)
	{
		// return offsetof(TClass, InClassField);
		return (int32)((int8*)&((TClass*)nullptr->*InClassField) - (int8*)nullptr);
	}
}
