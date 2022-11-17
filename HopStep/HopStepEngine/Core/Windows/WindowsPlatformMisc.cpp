#include "WindowsPlatformMisc.h"
#include "WindowsApplication.h"
#include "WindowsWindow.h"
#include "WindowsSystemIncludes.h"

extern "C"
{
	HINSTANCE GhInstance;
	int GCmdShow;
}

namespace HopStep
{
	HGenericApplication* HWindowsPlatformMisc::CreateApplication()
	{
		HGenericApplication* App = new HWindowsApplication(GhInstance);
		{
			App->SetWindow(std::make_shared<HWindowsWindow>(GhInstance, GCmdShow));
		}
		return App;
	}
}
