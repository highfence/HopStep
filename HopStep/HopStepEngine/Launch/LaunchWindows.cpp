#include "LaunchWindows.h"

#ifdef HopStep_On_Windows

INT WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
{
	std::cout << "Hello world!" << std::endl;
	system("pause");

	return 0;
}

#endif
