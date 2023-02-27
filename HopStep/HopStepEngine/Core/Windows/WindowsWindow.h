#pragma once
#include "..\GenericPlatform\GenericWindow.h"
#include "..\CoreExport.h"
#include "WindowsSystemIncludes.h"

namespace HopStep
{
	class HWindowsWindow : public HGenericWindow
	{
	public:

		HWindowsWindow(class HGenericApplication* App, HINSTANCE hInstance, int32 CmdShow);

		virtual uint32 GetClientWidth() override;
		virtual uint32 GetClientHeight() override;

		static HWND GetWindowHandle() { return WindowHandle; }

	private:

		static HWND WindowHandle;
	};
}
