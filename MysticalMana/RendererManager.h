#pragma once
#include <memory>
#include <vector>
#include <bgfx/bgfx.h>
#include <string>
#include "Window.h"
#include "Vertex.h"
#include "StaticEntity.h"

class RendererManager
{
	private:
		bgfx::VertexLayout vertex_layout_;
		bgfx::ProgramHandle shader_program_handle_;
		uint16_t view_width_;
		uint16_t view_height_;

	public:
		RendererManager(std::unique_ptr<Window>& window);
		~RendererManager();
		void PaintNextFrame(StaticEntity& static_entity);
		bgfx::VertexBufferHandle CreateVertexBuffer(std::vector<Vertex> vertices);
		bgfx::ProgramHandle LoadShaderProgram(std::string vertex_shader_path, std::string fragment_shader_path);
};

