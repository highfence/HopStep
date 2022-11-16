#include "GenericPlatformTime.h"

namespace HopStep
{
	double HGenericPlatformTime::SecondsPerCycle = 0;
	double HGenericPlatformTime::SecondsPerCycle64 = 0;
	double HGenericPlatformTime::LastIntervalCPUTimeInSeconds = 0;
}