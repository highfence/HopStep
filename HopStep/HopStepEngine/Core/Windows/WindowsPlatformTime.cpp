#include "WindowsPlatformTime.h"
#include "WindowsSystemIncludes.h"
#include "..\HopStepOverrides.h"

namespace HopStep
{
    double HWindowsPlatformTime::Init()
    {
        LARGE_INTEGER Frequency;
        ::QueryPerformanceFrequency(&Frequency);
        SecondsPerCycle = 1.0 / Frequency.QuadPart;
        SecondsPerCycle64 = 1.0 / Frequency.QuadPart;

        return Seconds();
    }

    double HWindowsPlatformTime::Seconds()
    {
        LARGE_INTEGER Cycles;
        ::QueryPerformanceCounter(&Cycles);

        return Cycles.QuadPart * SecondsPerCycle;
    }
}