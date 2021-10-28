#pragma once
#include "BaseEntity.h"
#include "Vertex.h"
#include <Buffer.h>
#include <BasicTypes.h>
#include <RefCntAutoPtr.hpp>
#include <vector>
#include <string>

struct StaticEntity : BaseEntity
{
	std::string mesh_file_name;
	std::vector<Vertex> m_vertices;
	std::vector<Diligent::Uint32> m_indices;
	Diligent::RefCntAutoPtr<Diligent::IBuffer> m_vertex_buffer;
	Diligent::RefCntAutoPtr<Diligent::IBuffer> m_index_buffer;
};

