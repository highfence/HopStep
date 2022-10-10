#include "TypeLibrary.h"
#include "Type.h"

namespace HopStep::CoreObject::Reflection
{
	void HType::RegisterToLibrary()
	{
		auto* Library = HTypeLibrary::GetPropertyPtr();
		Library->RegisterNewType(this);
	}
}
