#include "CoreGlobals.h"
#include "Misc/EngineConfig.h"

namespace HopStep
{
	bool GIsRequestingExit = false;
	bool IsEngineExitRequested()
	{
		return GIsRequestingExit;
	}

	void RequestEngineExit(const HString& Reason)
	{
		GIsRequestingExit = true;
	}

	HEngineConfig* GConfig = nullptr;
}