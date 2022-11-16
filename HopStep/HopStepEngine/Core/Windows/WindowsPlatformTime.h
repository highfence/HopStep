#pragma once
#include "..\GenericPlatform\GenericPlatformTime.h"

namespace HopStep
{
	struct HWindowsPlatformTime : public HGenericPlatformTime
	{
		static double Init();

		static double Seconds();

	protected:

	};

	typedef HWindowsPlatformTime HPlatfromTime;
}