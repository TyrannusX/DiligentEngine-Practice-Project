#ifndef STATICENTITY_H
#define STATICENTITY_H

#include "BaseEntity.h"
#include "Vertex.h"
#include <DiligentCore/Graphics/GraphicsEngine/interface/Texture.h>
#include <DiligentCore/Graphics/GraphicsEngine/interface/TextureView.h>
#include <DiligentCore/Graphics/GraphicsEngine/interface/Buffer.h>
#include <DiligentCore/Primitives/interface/BasicTypes.h>
#include <DiligentCore/Common/interface/RefCntAutoPtr.hpp>
#include <vector>
#include <string>

struct StaticEntity : BaseEntity
{
	std::string mesh_file_name;	
	std::vector<Vertex> m_vertices;
	std::vector<Diligent::Uint32> m_indices;
	Diligent::RefCntAutoPtr<Diligent::IBuffer> m_vertex_buffer;
	Diligent::RefCntAutoPtr<Diligent::IBuffer> m_index_buffer;
	Diligent::ITextureView* m_texture;
	std::string m_texture_file_path;
};
#endif