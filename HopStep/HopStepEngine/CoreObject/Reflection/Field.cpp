#include "Field.h"

namespace HopStep
{
	inline HField::HField(const HString& InName) : Name(InName) {}

	inline HField::~HField() {}

	inline const HString& HField::GetName() const { return Name; }
}
