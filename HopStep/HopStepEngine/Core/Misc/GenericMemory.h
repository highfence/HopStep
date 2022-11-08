#pragma once
#include "Core/HopStepOverrides.h"
#include "Core/PrimitiveTypeDefines.h"

namespace HopStep
{
	class HGenericMemory
	{
	public:

		static void MemSet(void* Dest, int32 value, HSize memorySize);

		static void MemCpy(void* Dest, void* Src, HSize Size);
	};
}