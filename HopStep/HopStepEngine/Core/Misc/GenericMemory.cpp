#include "HopStep.h"
#include "GenericMemory.h"

namespace HopStep
{
	void HGenericMemory::MemSet(void* Dest, int32 value, HSize memorySize)
	{
		std::memset(Dest, value, memorySize);
	}

	void HGenericMemory::MemCpy(void* Dest, void* Src, HSize Size)
	{
		std::memcpy(Dest, Src, Size);
	}

	void HGenericMemory::MemZero(void* Dest, HSize Size)
	{
		MemSet(Dest, 0, Size);
	}
}
