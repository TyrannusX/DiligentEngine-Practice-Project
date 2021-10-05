#pragma once
#include "BaseEntity.h"
#include "Vertex.h"
#include <glm/vec3.hpp>
#include <bgfx/bgfx.h>
#include <vector>

struct StaticEntity : BaseEntity
{
	std::vector<Vertex> vertices;
	bgfx::VertexBufferHandle vertex_buffer_handle;
};

