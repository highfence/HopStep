#include "WindowsApplication.h"
#include "WindowsApplicationMessageHandler.h"
#include "..\CoreGlobals.h"

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

		MessageHander = std::make_shared<HWindowsApplicationMessageHandler>();
	}

	void HWindowsApplication::SetWindow(TSharedPtr<HGenericWindow> Window)
	{
		NativeWindow = std::move(Window);
	}

	LRESULT HWindowsApplication::AppWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		HGenericApplication* App = reinterpret_cast<HGenericApplication*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

		switch (msg)
		{
		case WM_CREATE:
		{
			LPCREATESTRUCT CreateStruct = reinterpret_cast<LPCREATESTRUCT>(lParam);
			SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(CreateStruct->lpCreateParams));
			break;
		}

		case WM_CLOSE:
			DestroyWindow(hwnd);
			break;

		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		case WM_KEYDOWN:
			App->GetMessageHandler().get()->HandleKeyDown(
					reinterpret_cast<uint64*>(wParam), 
					reinterpret_cast<uint64*>(lParam)
				);
			break;

		case WM_KEYUP:
			App->GetMessageHandler().get()->HandleKeyUp(
				reinterpret_cast<uint64*>(wParam),
				reinterpret_cast<uint64*>(lParam)
			);
			break;

		default:
			return DefWindowProc(hwnd, msg, wParam, lParam);
		}
		return 0;
	}

	TSharedPtr<HGenericWindow> HWindowsApplication::GetWindow()
	{
		return NativeWindow;
	}

	void HWindowsApplication::PumpMessages(float DeltaTime)
	{
		MSG Message;

		while (PeekMessage(&Message, NULL, 0, 0, PM_REMOVE))
		{
			if (Message.message == WM_QUIT)
			{
				RequestEngineExit(TEXT("WM_QUIT"));
				break;
			}

			TranslateMessage(&Message);
			DispatchMessageW(&Message);
		}
	}

	TSharedPtr<HGenericApplicationMessageHandler> HWindowsApplication::GetMessageHandler()
	{
		return MessageHander;
	}
}