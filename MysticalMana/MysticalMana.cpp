#include <iostream>
#include <memory>
#include "Application.h"

int main()
{
	try
	{
		std::unique_ptr<Application> game(new Application());
		game->Run();
	}
	catch (const std::exception& ex)
	{
		std::cerr << ex.what() << std::endl;
	}
	return 0;
}
