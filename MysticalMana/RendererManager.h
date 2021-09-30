#pragma once
#include <memory>
#include "Window.h"

class RendererManager
{
	public:
		RendererManager(std::unique_ptr<Window>& window);
};

