#pragma once
#include <memory>
#include <vector>
#include <bgfx/bgfx.h>
#include "Window.h"
#include "Vertex.h"

class RendererManager
{
	private:
		bgfx::VertexLayout vertex_layout_;

	public:
		RendererManager(std::unique_ptr<Window>& window);
		void PaintNextFrame();
		bgfx::VertexBufferHandle CreateVertexBuffer(std::vector<Vertex> vertices);
};

