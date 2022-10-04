#include "LaunchWindows.h"
#include "Core/Misc/EngineConfig.h"
#include "Core/Misc/Paths.h"

#ifdef HopStep_On_Windows

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
{
	std::cout << "Hello world!" << std::endl;
	system("pause");

	return 0;
}

#endif
