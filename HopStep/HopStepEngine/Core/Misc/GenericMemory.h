#pragma once
#include "Core/HopStepOverrides.h"
#include "Core/PrimitiveTypeDefines.h"

namespace HopStep
{
	class HGenericMemory
	{
	public:

		static void MemSet(void* Dest, int32 value, Size_t memorySize);

		static void MemCpy(void* Dest, void* Src, Size_t Size);

		static void MemZero(void* Dest, Size_t Size);
	};
}