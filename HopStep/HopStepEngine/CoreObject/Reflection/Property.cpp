#include "Property.h"

namespace HopStep
{
	HProperty::HProperty(const HString& InName, int32 InOffset, int32 InElementSize, int32 InArrayDimension)
		: HType(InName)
		, Offset(InOffset)
		, ElementSize(InElementSize)
		, ArrayDimension(InArrayDimension)
		, PropertyFlags(0u)
	{
		TotalSize = ElementSize * ArrayDimension;
	}

	HProperty::~HProperty() {}

	void HProperty::SetPropertyFlag(EPropertyFlag Flag) { PropertyFlags |= static_cast<uint64>(Flag); }

	bool HProperty::GetPropertyFlag(EPropertyFlag Flag) const { return PropertyFlags & static_cast<uint64>(Flag); }

}
