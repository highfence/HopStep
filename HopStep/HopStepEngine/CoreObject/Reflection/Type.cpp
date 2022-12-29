#include "Type.h"

namespace HopStep
{
	HType::HType(const HString& InName) : Name(InName) {}

	HType::~HType() {}

	const HString& HType::GetName() const { return Name; }
}
