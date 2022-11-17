#include "WindowsWindow.h"

namespace HopStep
{
	HWindowsWindow::HWindowsWindow(HINSTANCE hInstance, int32 CmdShow)
	{
		uint32 ClientWidth = 1200;
		uint32 ClientHeight = 800;

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
}