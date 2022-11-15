#pragma once
#include "..\PrimitiveTypeDefines.h"
#include "..\HopStepOverrides.h"

namespace HopStep
{
	struct HCommandLine
	{
		static constexpr uint32 MaxCommandLine = 1 << 14;

		static bool IsInit();

		static const HChar* Get();

		static bool Set(const HChar* CmdLine);

	private:

		static bool bInit;
		static HChar CommandLine[MaxCommandLine];
	};
}