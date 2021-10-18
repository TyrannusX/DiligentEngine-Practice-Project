/*
* Force GLFW to expose native window handle
*/

#define GLFW_EXPOSE_NATIVE_WIN32 1

/*
* windows.h defines its own versions of these functions
*/
#define NOMINMAX

#include <iostream>
#include "RendererManager.h"
#include "Vertex.h"
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <fstream>
#include <exception>

RendererManager::RendererManager(Window* window)
{
	//Get underlying window and details
	GLFWwindow* underlyingWindow = window->GetUnderlyingWindow();
	
	int windowWidth;
	int windowHeight;
	glfwGetWindowSize(underlyingWindow, &windowWidth, &windowHeight);
	HWND nativeOsWindow = glfwGetWin32Window(underlyingWindow);

	view_width_ = (uint16_t)windowWidth;
	view_height_ = (uint16_t)windowHeight;

	//Initialize Vulkan Device, Context, and Swap Chain
	Diligent::IEngineFactoryVk* engineFactory = Diligent::GetEngineFactoryVk();
	Diligent::EngineVkCreateInfo createInfo;
	engineFactory->CreateDeviceAndContextsVk(createInfo, &render_device_, &immediate_context_);
	Diligent::SwapChainDesc swapChainDesc;
	Diligent::Win32NativeWindow diligentNativeWindowHandle{ nativeOsWindow };
	engineFactory->CreateSwapChainVk(render_device_, immediate_context_, swapChainDesc, diligentNativeWindowHandle, &swap_chain_);

	//Initialize graphics/compute pipeline
}

RendererManager::~RendererManager()
{

}

void RendererManager::PaintNextFrame(StaticEntity& static_entity, int x_modifier, int y_modifier)
{

}