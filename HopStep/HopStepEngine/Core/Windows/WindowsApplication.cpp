#include "WindowsApplication.h"

namespace HopStep
{
	HWindowsApplication::HWindowsApplication(HINSTANCE hInstanceHandle)
		: InstanceHandle(hInstanceHandle)
	{
		// Create Windows Class and register.
		{
			WNDCLASSEX Wc;
			HGenericMemory::MemSet(&Wc, 0, sizeof(Wc));

			Wc.cbSize = sizeof(WNDCLASSEX);
			Wc.style = CS_DBLCLKS;
			Wc.lpfnWndProc = AppWndProc;
			Wc.cbClsExtra = 0;
			Wc.cbWndExtra = 0;
			Wc.hInstance = InstanceHandle;
			Wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
			Wc.hCursor = LoadCursor(NULL, IDC_ARROW);
			Wc.hbrBackground = NULL;
			Wc.lpszMenuName = NULL;
			Wc.lpszClassName = TEXT("HopStep");
			Wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

			if (::RegisterClassEx(&Wc) == false)
			{
				HCheck(false);
			}
		}
	}

	void HWindowsApplication::SetWindow(std::shared_ptr<HGenericWindow> Window)
	{
		NativeWindow = std::move(Window);
	}

	LRESULT HWindowsApplication::AppWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg)
		{
		case WM_CLOSE:
			DestroyWindow(hwnd);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hwnd, msg, wParam, lParam);
		}
		return 0;
	}

	void HWindowsApplication::PumpMessages(float DeltaTime)
	{
		MSG Message;

		while (PeekMessage(&Message, NULL, 0, 0, PM_REMOVE))
		{
			if (Message.message == WM_QUIT)
			{
				break;
			}

			TranslateMessage(&Message);
			DispatchMessageW(&Message);
		}
	}
}