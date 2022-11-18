#pragma once
#include "..\CoreStandardIncludes.h"

#define SAFE_RELEASE(p) { if (p) { (p)->Release(); (p)=nullptr; } }

extern "C" HINSTANCE GhInstance;
extern "C" int GCmdShow;
extern "C" HWND GWindowHandle;



