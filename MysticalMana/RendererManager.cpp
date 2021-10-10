#define GLFW_EXPOSE_NATIVE_WIN32
#include <iostream>
#include "RendererManager.h"
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <fstream>
#include <exception>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

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
	initParameters.type = bgfx::RendererType::OpenGL;
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

	view_width_ = (uint16_t)windowWidth;
	view_height_ = (uint16_t)windowHeight;
	bgfx::setViewRect(0, 0, 0, view_width_, view_height_);
	bgfx::touch(0);
	bgfx::dbgTextPrintf(0, 1, 0x0f, "Mystical Mana Debug Build\0");
	bgfx::frame();

	shader_program_handle_ = LoadShaderProgram("vertex.bin", "fragment.bin");
}

RendererManager::~RendererManager()
{
	bgfx::shutdown();
}

void RendererManager::PaintNextFrame(StaticEntity& static_entity)
{
	/*
	* Imagine moving the camera around the world.
	* Define the camera's position.
	* This is the view matrix
	*/
	glm::vec3 camera_looks_at_this_point = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 camera_position = glm::vec3(0.0f, 0.0f, 10.0f);
	glm::mat4 camera_position_in_world_view_matrix = glm::lookAt(camera_position, camera_looks_at_this_point, glm::vec3(0.0f, 1.0f, 0.0f));

	/*
	* Once the camera is positioned, imagine adjusting the lens settings.
	* Such as controling the zoom levels and focus.
	* This is the projection matrix
	*/
	glm::mat4 camera_zoom_focus_projection_matrix = glm::perspective(60.0f, (float)(4.0f / 3.0f), 0.1f, 100.0f);

	/*
	* Model matrix
	*/
	glm::mat4 model_matrix = glm::mat4(0.0f);


	/*
	* Define the MVP
	*/
	glm::mat4 the_world_model_view_projection_matrix = camera_zoom_focus_projection_matrix * camera_position_in_world_view_matrix * model_matrix;

	bgfx::setViewTransform(0, &camera_position_in_world_view_matrix, &camera_zoom_focus_projection_matrix);
	bgfx::setViewRect(0, 0, 0, view_width_, view_height_);
	bgfx::touch(0);
	bgfx::setTransform(&model_matrix);
	bgfx::setVertexBuffer(0, static_entity.vertex_buffer_handle);
	bgfx::setState(BGFX_STATE_DEFAULT);
	bgfx::submit(0, shader_program_handle_);
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