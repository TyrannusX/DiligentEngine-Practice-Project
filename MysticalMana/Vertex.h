#pragma once
#include <BasicMath.hpp>

/*
* Representation of a vertex.
* 
* IMPORTANT NOTE
* This struct must match the struct found in the shader.
*/
struct Vertex
{
	Diligent::float3 position;
	Diligent::float4 color;
};

