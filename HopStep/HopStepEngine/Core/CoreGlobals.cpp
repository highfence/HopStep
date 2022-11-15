#include "CoreGlobals.h"
#include "Misc/EngineConfig.h"

namespace HopStep
{
	bool GIsRequestingExit = false;
	bool IsEngineExitRequested()
	{
		return GIsRequestingExit;
	}

	HEngineConfig* GConfig = nullptr;
}