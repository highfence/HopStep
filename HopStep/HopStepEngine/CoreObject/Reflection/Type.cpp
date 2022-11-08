#include "TypeLibrary.h"
#include "Type.h"

namespace HopStep
{
	void HType::RegisterToLibrary()
	{
		auto* Library = HTypeLibrary::GetPropertyPtr();
		Library->RegisterNewType(this);
	}
}
