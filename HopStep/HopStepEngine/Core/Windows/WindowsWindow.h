#pragma once
#include "..\GenericPlatform\GenericWindow.h"
#include "..\CoreExport.h"
#include "WindowsSystemIncludes.h"

namespace HopStep
{
	class HWindowsWindow : public HGenericWindow
	{
	public:

		HWindowsWindow(HINSTANCE hInstance, int32 CmdShow);

	private:

		HWND WindowHandle;
	};
}
