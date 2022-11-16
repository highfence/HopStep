#pragma once

namespace HopStep
{
	struct HGenericPlatformTime
	{

	protected:

		static double SecondsPerCycle;
		static double SecondsPerCycle64;
		static double LastIntervalCPUTimeInSeconds;
	};
}