#define GLFW_EXPOSE_NATIVE_WIN32
#include "RendererManager.h"
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <bgfx/bgfx.h>

RendererManager::RendererManager(std::unique_ptr<Window>& window)
{
	std::unique_ptr<GLFWwindow, GlfwWindowDestroyer>& underlyingWindow = window->GetUnderlyingWindow();
	
	std::unique_ptr<int> windowWidth;
	std::unique_ptr<int> windowHeight;
	glfwGetWindowSize(underlyingWindow.get(), windowWidth.get(), windowHeight.get());
	HWND nativeOsWindow = glfwGetWin32Window(underlyingWindow.get());
	
	bgfx::Init initParameters;
	initParameters.type = bgfx::RendererType::Vulkan;
	initParameters.vendorId = BGFX_PCI_ID_NVIDIA;
	initParameters.resolution.width = (uint32_t)windowWidth.get();
	initParameters.resolution.height = (uint32_t)windowHeight.get();
	initParameters.resolution.reset = BGFX_RESET_VSYNC;
	initParameters.platformData.nwh = nativeOsWindow;
	bgfx::init(initParameters);
	bgfx::setDebug(BGFX_DEBUG_TEXT);
	bgfx::setViewClear(0
		, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH
		, 0x303030ff
		, 1.0f
		, 0
	);
	bgfx::touch(0);
	bgfx::frame();
}