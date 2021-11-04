/*
* Define macros for Diligent Engine
*/
#ifdef _WIN32
	#define PLATFORM_WIN32 1
#elif _WIN64
	#define PLATFORM_WIN32 1
#elif __linux__
	#define PLATFORM_LINUX 1
#endif

#include <iostream>
#include <memory>
#include "Application.h"

int main()
{
	std::unique_ptr<Application> game(new Application());
	game->Run();
	return 0;
}
