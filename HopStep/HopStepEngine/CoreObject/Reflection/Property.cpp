#include "Property.h"
#include "FieldClass.h"

namespace HopStep
{
	// Todo: fix this passing nullptr
	HProperty::HProperty(const HString& InName, int32 InOffset, int32 InElementSize, int32 InArrayDimension)
		: HField(InName, nullptr)
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
