#include "LaunchWindows.h"
#include "Core/Misc/EngineConfig.h"
#include "Core/Misc/Paths.h"

#ifdef HopStep_On_Windows

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ PSTR lpCmdLine,
	_In_ INT nCmdShow)
{


	system("pause");

	return 0;
}

#endif
