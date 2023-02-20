#pragma once
#include "..\CoreExport.h"

namespace HopStep
{
	struct HStringUtil
	{
		/*
			Needs delete[] to result ptr
		*/
		static char* AllocateNewCharFromHChar(const HChar* Src);
	};
}