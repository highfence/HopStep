#include "CoreGlobals.h"
#include "Windows/WindowsPlatformTime.h"
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

	double GStartTime = HPlatfromTime::Init();
}