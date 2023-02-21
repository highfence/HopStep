#include "TypeLibrary.h"


namespace HopStep
{
	HTypeLibrary::~HTypeLibrary()
	{
	}

	HTypeLibrary* HTypeLibrary::GetPropertyPtr()
	{
		static HTypeLibrary Library;
		return &Library;
	}
}
	

