#include "StringUtil.h"

namespace HopStep
{
	char* HStringUtil::AllocateNewCharFromHChar(const HChar* Src)
	{
		int32 Size = WideCharToMultiByte(CP_ACP, 0, Src, -1, NULL, 0, NULL, NULL);

		char* Result = new char[Size];
		WideCharToMultiByte(CP_ACP, 0, Src, -1, Result, Size, 0, 0);
		return Result;
	}
}
