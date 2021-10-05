#define GLFW_EXPOSE_NATIVE_WIN32
#include <iostream>
#include "RendererManager.h"
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>

RendererManager::RendererManager(std::unique_ptr<Window>& window)
{
	std::unique_ptr<GLFWwindow, GlfwWindowDestroyer>& underlyingWindow = window->GetUnderlyingWindow();
	
	int windowWidth;
	int windowHeight;
	glfwGetWindowSize(underlyingWindow.get(), &windowWidth, &windowHeight);
	HWND nativeOsWindow = glfwGetWin32Window(underlyingWindow.get());
	
	//IMPORTANT: this call forces BGFX to use same thread as window
	/*bgfx::renderFrame();*/

	std::cout << windowWidth << std::endl;

	bgfx::Init initParameters;
	initParameters.type = bgfx::RendererType::Direct3D12;
	initParameters.vendorId = BGFX_PCI_ID_NVIDIA;
	initParameters.resolution.width = (uint32_t)windowWidth;
	initParameters.resolution.height = (uint32_t)windowHeight;
	initParameters.resolution.reset = BGFX_RESET_VSYNC;
	initParameters.platformData.nwh = nativeOsWindow;
	bgfx::init(initParameters);
	bgfx::setViewClear(0
		, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH
		, 0x303030ff
		, 1.0f
		, 0
	);

	vertex_layout_
		.begin()
		.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
		.add(bgfx::Attrib::Color0, 3, bgfx::AttribType::Float)
		.end();

	bgfx::setDebug(BGFX_DEBUG_TEXT);
	bgfx::setViewRect(0, 0, 0, (uint16_t)windowWidth, (uint16_t)windowHeight);
	bgfx::touch(0);
	bgfx::dbgTextPrintf(0, 1, 0x0f, "Mystical Mana Debug Build\0");
	bgfx::frame();
}

void RendererManager::PaintNextFrame()
{
	/*bgfx::setViewRect(0, 0, 0, (uint16_t)windowWidth.get(), (uint16_t)windowHeight.get());*/
	bgfx::touch(0);
	bgfx::dbgTextClear();
	bgfx::dbgTextPrintf(0, 1, 0x0f, "Mystical Mana Debug Build\0");
	bgfx::frame();
}

bgfx::VertexBufferHandle RendererManager::CreateVertexBuffer(std::vector<Vertex> vertices)
{
	return bgfx::createVertexBuffer(
		bgfx::makeRef(
			vertices.data(),
			vertices.size()
		),
		vertex_layout_
	);
}