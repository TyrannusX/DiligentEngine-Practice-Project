#pragma once
#include <vector>
#include <string>
#include "Vertex.h"

class AssetManager
{
	public:
		std::vector<Vertex> GetMeshVertices(const std::string& file_path);
};

