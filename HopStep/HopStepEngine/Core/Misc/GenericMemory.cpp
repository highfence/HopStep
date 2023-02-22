#include "HopStep.h"
#include "GenericMemory.h"

namespace HopStep
{
	void HGenericMemory::MemSet(void* Dest, int32 value, Size_t memorySize)
	{
		std::memset(Dest, value, memorySize);
	}

	void HGenericMemory::MemCpy(void* Dest, void* Src, Size_t Size)
	{
		std::memcpy(Dest, Src, Size);
	}

	void HGenericMemory::MemZero(void* Dest, Size_t Size)
	{
		MemSet(Dest, 0, Size);
	}
}
