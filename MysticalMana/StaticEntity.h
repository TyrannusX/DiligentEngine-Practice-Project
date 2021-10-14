#pragma once
#include "BaseEntity.h"
#include "Vertex.h"
#include <glm/vec3.hpp>
#include <bgfx/bgfx.h>

struct StaticEntity : BaseEntity
{
	Vertex* vertices;
	uint16_t* indices;
	bgfx::VertexBufferHandle vertex_buffer_handle;
	bgfx::IndexBufferHandle index_buffer_handle;
};

