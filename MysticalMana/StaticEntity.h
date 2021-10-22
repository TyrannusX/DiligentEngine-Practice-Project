#pragma once
#include "BaseEntity.h"
#include "Vertex.h"
#include <Buffer.h>
#include <BasicTypes.h>
#include <RefCntAutoPtr.hpp>
#include <vector>

struct StaticEntity : BaseEntity
{
	std::vector<Vertex> vertices;
	std::vector<Diligent::Uint32> indices;
	Diligent::RefCntAutoPtr<Diligent::IBuffer> vertex_buffer;
	Diligent::RefCntAutoPtr<Diligent::IBuffer> index_buffer;
};

