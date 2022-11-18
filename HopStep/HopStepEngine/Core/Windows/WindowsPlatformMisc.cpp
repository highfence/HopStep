#include "WindowsPlatformMisc.h"
#include "WindowsApplication.h"
#include "WindowsWindow.h"
#include "WindowsSystemIncludes.h"

extern "C"
{
	HINSTANCE GhInstance;
	int GCmdShow;
	HWND GWindowHandle;
}

namespace HopStep
{
	HGenericApplication* HWindowsPlatformMisc::CreateApplication()
	{
		HGenericApplication* App = new HWindowsApplication(GhInstance);
		{
			std::shared_ptr<HWindowsWindow> Window = std::make_shared<HWindowsWindow>(GhInstance, GCmdShow);
			App->SetWindow(Window);
			GWindowHandle = Window->GetWindowHandle();
		}
		return App;
	}


}
