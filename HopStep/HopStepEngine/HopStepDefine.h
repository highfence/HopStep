#pragma once

#if defined(_WIN64)
#define HopStep_Windows64 1
#elif defined(_WIN32)
#define HopStep_Windows32 1
#endif

#define HopStep_On_Windows HopStep_Windows64 | HopStep_Windows32

#define HopStep_UnitTest 1


