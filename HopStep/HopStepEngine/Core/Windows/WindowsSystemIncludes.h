#pragma once
#include "..\CoreStandardIncludes.h"
#include "..\HopStepOverrides.h"
#include "..\PrimitiveTypeDefines.h"
#include "..\Misc\DebugUtils.h"

#if defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

extern "C" HINSTANCE GhInstance;
extern "C" int GCmdShow;
extern "C" HWND GWindowHandle;



