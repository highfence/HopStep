#include "Field.h"

namespace HopStep
{
	HField::HField(const HString& InName) : Name(InName) {}

	HField::~HField() {}

	const HString& HField::GetName() const { return Name; }
}
