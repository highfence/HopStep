#include "..\..\HopStep.h"
#include "..\Engine\EngineLoop.h"

namespace HopStep
{
	HEngineLoop GEngineLoop;

	int32 GuardedMain(const HopStep::HChar* CommandLine)
	{
		if (HopStep::HCommandLine::Set(CommandLine) == false)
		{
			return -1;
		}

		int32 ErrorLevel = 0;

		ErrorLevel = HopStep::GEngineLoop.Init(CommandLine);

		while (!HopStep::IsEngineExitRequested())
		{
			HopStep::GEngineLoop.Tick();
		}

		HopStep::GEngineLoop.Exit();

		return ErrorLevel;
	}
}
