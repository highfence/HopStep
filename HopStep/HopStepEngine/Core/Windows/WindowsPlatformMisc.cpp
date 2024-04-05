#include "WindowsPlatformMisc.h"
#include "WindowsApplication.h"
#include "WindowsWindow.h"
#include "WindowsSystemIncludes.h"
#include "Core/Misc/App.h"

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
			TSharedPtr<HWindowsWindow> Window = std::make_shared<HWindowsWindow>(App, GhInstance, GCmdShow);
			App->SetWindow(Window);
			GWindowHandle = Window->GetWindowHandle();
		}
		HApp::GApp = App;
		return App;
	}


}
