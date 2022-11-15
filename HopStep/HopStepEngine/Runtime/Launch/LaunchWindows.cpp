#include "LaunchWindows.h"
#include "Core/Misc/EngineConfig.h"
#include "Core/Misc/Paths.h"

#ifdef HopStep_On_Windows

extern int32 GuardedMain(const HopStep::HChar* CommandLine);

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ PSTR lpCmdLine,
	_In_ INT nCmdShow)
{
	const HopStep::HChar* CmdLine = ::GetCommandLineW();
	int32 ExitValue = GuardedMain(CmdLine);
	return ExitValue;
}

#endif
