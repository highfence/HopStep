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

		virtual uint32 GetClientWidth() override;
		virtual uint32 GetClientHeight() override;

		HWND GetWindowHandle() const { return WindowHandle; }

	private:

		HWND WindowHandle;
	};
}
