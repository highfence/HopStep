#include "HopStep.h"
#include "MetadataLibrary.h"

namespace HopStep::Reflection
{
	std::vector<class HType*> HMetadataLibrary::GetTypes()
	{
		return Types;
	}
}
