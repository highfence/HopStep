#include "WindowsWindow.h"
#include "Core\CoreGlobals.h"

namespace HopStep
{
	HWND HWindowsWindow::WindowHandle = nullptr;

	HWindowsWindow::HWindowsWindow(HINSTANCE hInstance, int32 CmdShow)
	{
		WindowHandle = CreateWindowEx(
			WS_EX_CLIENTEDGE,
			TEXT("HopStep"),
			TEXT("HopStep"),
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ClientWidth,
			ClientHeight,
			NULL,
			NULL,
			hInstance,
			NULL
		);

		if (WindowHandle == NULL)
		{
			HCheck(false);
		}

		ShowWindow(WindowHandle, CmdShow);
		UpdateWindow(WindowHandle);
	}

	uint32 HWindowsWindow::GetClientWidth()
	{
		return ClientWidth;
	}

	uint32 HWindowsWindow::GetClientHeight()
	{
		return ClientHeight;
	}
}