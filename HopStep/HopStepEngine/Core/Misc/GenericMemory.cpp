#include "HopStep.h"
#include "GenericMemory.h"

namespace HopStep::Core::Misc
{
	void HGenericMemory::MemSet(void* Dest, int32 value, HSize memorySize)
	{
		std::memset(Dest, value, memorySize);
	}

	void HGenericMemory::MemCpy(void* Dest, void* Src, HSize Size)
	{
		std::memcpy(Dest, Src, Size);
	}
}
