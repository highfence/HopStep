#pragma once
#include "..\CoreStandardIncludes.h"
#include "..\HopStepOverrides.h"

#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#include <wrl.h>

#define SAFE_RELEASE(p) { if (p) { (p)->Release(); (p)=nullptr; } }

extern "C" HINSTANCE GhInstance;
extern "C" int GCmdShow;
extern "C" HWND GWindowHandle;



