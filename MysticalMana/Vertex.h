#ifndef VERTEX_H
#define VERTEX_H

#include <DiligentCore/Common/interface/BasicMath.hpp>

/*
* Representation of a vertex.
* 
* IMPORTANT NOTE
* This struct must match the struct found in the shader.
*/
struct Vertex
{
	Diligent::float3 m_position;
	Diligent::float2 m_texture_coordinate;
};
#endif