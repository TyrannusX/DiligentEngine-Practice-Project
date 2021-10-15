#pragma once
#include "BaseEntity.h"
#include "Vertex.h"
#include <glm/vec3.hpp>

struct StaticEntity : BaseEntity
{
	Vertex* vertices;
	uint16_t* indices;
};

