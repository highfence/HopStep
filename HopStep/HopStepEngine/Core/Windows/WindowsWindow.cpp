#include "WindowsWindow.h"
#include "Core\CoreGlobals.h"
#include "Core\GenericPlatform\GenericApplication.h"

namespace HopStep
{
	HWND HWindowsWindow::WindowHandle = nullptr;

	HWindowsWindow::HWindowsWindow(HGenericApplication* App, HINSTANCE hInstance, int32 CmdShow)
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
			NULL, // No parent window
			NULL, // No using menu
			hInstance,
			App
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