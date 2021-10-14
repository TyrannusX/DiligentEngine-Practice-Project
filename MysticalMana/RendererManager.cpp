/*
* Force GLFW to expose native window handle
*/
#define GLFW_EXPOSE_NATIVE_WIN32

/*
* windows.h defines its own versions of these functions
*/
#define NOMINMAX

#include <iostream>
#include "RendererManager.h"
#include "Vertex.h"
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <fstream>
#include <exception>
#include <bx/math.h>

RendererManager::RendererManager(Window* window)
{
	GLFWwindow* underlyingWindow = window->GetUnderlyingWindow();
	
	int windowWidth;
	int windowHeight;
	glfwGetWindowSize(underlyingWindow, &windowWidth, &windowHeight);
	HWND nativeOsWindow = glfwGetWin32Window(underlyingWindow);
	
	//IMPORTANT: this call forces BGFX to use same thread as window
	//bgfx::renderFrame();

	bgfx::Init initParameters;
	initParameters.type = bgfx::RendererType::Direct3D11;
	initParameters.vendorId = BGFX_PCI_ID_NVIDIA;
	initParameters.resolution.width = (uint32_t)windowWidth;
	initParameters.resolution.height = (uint32_t)windowHeight;
	initParameters.resolution.reset = BGFX_RESET_VSYNC;
	initParameters.platformData.nwh = nativeOsWindow;
	initParameters.callback = &callbacker;
	bgfx::init(initParameters);

	vertex_layout_
		.begin()
		.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
		.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
		.end();

	bgfx::setDebug(BGFX_DEBUG_TEXT);

	view_width_ = (uint16_t)windowWidth;
	view_height_ = (uint16_t)windowHeight;
	bgfx::reset(view_width_, view_height_, BGFX_RESET_VSYNC);
	bgfx::setViewRect(0, 0, 0, view_width_, view_height_);
	bgfx::touch(0);
	bgfx::setViewClear(0
		, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH
		, 0x443355FF
		, 1.0f
		, 0
	);
	bgfx::dbgTextPrintf(0, 1, 0x0f, "Mystical Mana Debug Build\0");
	bgfx::frame();

	shader_program_handle_ = LoadShaderProgram("vertex.bin", "fragment.bin");
}

RendererManager::~RendererManager()
{
	bgfx::shutdown();
}

void RendererManager::PaintNextFrame(StaticEntity& static_entity, int x_modifier, int y_modifier)
{
	/*
	* Imagine moving the camera around the world.
	* Define the camera's position.
	* This is the view matrix
	*/
	const bx::Vec3 camera_looks_at = { 0.0f, 0.0f, 0.0f };
	const bx::Vec3 camera_position = { 0.0f, 0.0f, 1.0f };
	float view_matrix[16];
	bx::mtxLookAt(view_matrix, camera_position, camera_looks_at);

	/*
	* Once the camera is positioned, imagine adjusting the lens settings.
	* Such as controling the zoom levels and focus.
	* This is the projection matrix
	*/
	float projection_matrix[16];
	bx::mtxProj(projection_matrix, 60.0f, float(view_width_)/float(view_height_), 0.1f, 100.0f, bgfx::getCaps()->homogeneousDepth);

	/*
	* Define translation matrix for primitives
	*/
	float translation_matrix[16];
	bx::mtxRotateY(translation_matrix, 0.0f);
	translation_matrix[12] = 0.0f;
	translation_matrix[13] = 0.0f;
	translation_matrix[14] = 0.0f;

	bgfx::touch(0);
	bgfx::setViewTransform(0, view_matrix, projection_matrix);
	/*bgfx::setViewRect(0, 0, 0, view_width_, view_height_);*/
	bgfx::setTransform(translation_matrix);
	bgfx::setVertexBuffer(0, static_entity.vertex_buffer_handle);
	bgfx::setIndexBuffer(static_entity.index_buffer_handle);
	bgfx::setState(BGFX_STATE_DEFAULT);
	bgfx::submit(0, shader_program_handle_);
	bgfx::dbgTextClear();
	bgfx::dbgTextPrintf(0, 1, 0x0f, "Mystical Mana Debug Build\0");

	bgfx::frame();
}

bgfx::VertexBufferHandle RendererManager::CreateVertexBuffer(Vertex* vertices)
{
	return bgfx::createVertexBuffer(
		bgfx::makeRef(
			vertices,
			sizeof(vertices)
		),
		vertex_layout_
	);
}

bgfx::IndexBufferHandle RendererManager::CreateIndexBuffer(uint16_t* indices)
{
	return bgfx::createIndexBuffer(
		bgfx::makeRef(
			indices,
			sizeof(indices)
		)
	);
}

bgfx::ProgramHandle RendererManager::LoadShaderProgram(std::string vertex_shader_path, std::string fragment_shader_path)
{
	char* vertex_shader_data = new char[2048];
	std::ifstream vertex_shader_file_handle;
	size_t vertex_shader_file_size;
	vertex_shader_file_handle.open(vertex_shader_path);

	if (!vertex_shader_file_handle.is_open())
	{
		throw std::exception("Failed to open vertex shader file");
	}

	vertex_shader_file_handle.seekg(0, std::ios::end);
	vertex_shader_file_size = vertex_shader_file_handle.tellg();
	vertex_shader_file_handle.seekg(0, std::ios::beg);
	vertex_shader_file_handle.read(vertex_shader_data, vertex_shader_file_size);
	vertex_shader_file_handle.close();
	const bgfx::Memory* vertex_shader_memory = bgfx::copy(vertex_shader_data, vertex_shader_file_size + 1);
	vertex_shader_memory->data[vertex_shader_memory->size - 1] = '\0';
	bgfx::ShaderHandle bgfx_vertex_handle = bgfx::createShader(vertex_shader_memory);
	bgfx::setName(bgfx_vertex_handle, "VERTEX_SHADER");

	char* fragment_shader_data = new char[2048];
	std::ifstream fragment_shader_file_handle;
	size_t fragment_shader_file_size;
	fragment_shader_file_handle.open(fragment_shader_path);

	if (!fragment_shader_file_handle.is_open())
	{
		throw std::exception("Failed to open fragment shader file");
	}

	fragment_shader_file_handle.seekg(0, std::ios::end);
	fragment_shader_file_size = fragment_shader_file_handle.tellg();
	fragment_shader_file_handle.seekg(0, std::ios::beg);
	fragment_shader_file_handle.read(fragment_shader_data, fragment_shader_file_size);
	fragment_shader_file_handle.close();
	const bgfx::Memory* fragment_shader_memory = bgfx::copy(fragment_shader_data, fragment_shader_file_size + 1);
	fragment_shader_memory->data[fragment_shader_memory->size - 1] = '\0';
	bgfx::ShaderHandle bgfx_fragment_handle = bgfx::createShader(fragment_shader_memory);
	bgfx::setName(bgfx_fragment_handle, "FRAGMENT_SHADER");

	return bgfx::createProgram(bgfx_vertex_handle, bgfx_fragment_handle, true);
}