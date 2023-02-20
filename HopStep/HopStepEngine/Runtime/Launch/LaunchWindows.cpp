#include "LaunchWindows.h"
#include "Core/Misc/EngineConfig.h"
#include "Core/Misc/Paths.h"
#include "Core/Windows/WindowsSystemIncludes.h"
#include "Launch.h"

#ifdef HopStep_On_Windows

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ PSTR lpCmdLine,
	_In_ INT nCmdShow)
{
	GhInstance = hInstance;
	GCmdShow = nCmdShow;

	const HopStep::HChar* CmdLine = ::GetCommandLineW();
	int32 ExitValue = HopStep::GuardedMain(CmdLine);
	return ExitValue;
}

#endif
