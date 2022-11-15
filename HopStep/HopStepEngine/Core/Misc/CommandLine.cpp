#include "CommandLine.h"
#include "DebugUtils.h"
#include "..\Templates\HopStepTemplates.h"

namespace HopStep
{
	bool HCommandLine::bInit = false;
	HChar HCommandLine::CommandLine[HCommandLine::MaxCommandLine] = TEXT("");

	bool HCommandLine::IsInit()
	{
		return bInit;
	}

	const HChar* HCommandLine::Get()
	{
		HCheck(bInit);
		return CommandLine;
	}

	bool HCommandLine::Set(const HChar* CmdLine)
	{
		// Todo: Wrap with platform string
		wcsncpy_s(CommandLine, HOPSTEP_ARRAY_COUNT(CommandLine), CmdLine, HOPSTEP_ARRAY_COUNT(CommandLine));

		bInit = true;

		return bInit;
	}
}
