#include "AssetManager.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <exception>

std::vector<Vertex> AssetManager::GetMeshVertices(const std::string& file_path)
{
	std::vector<Vertex> final_vertices;

	/* 
	* Instantiate the mesh scene from file(basically represents object / scene space).
	* 
	* The post processing flags transform the data from the file.
	* Triangulate will ensure that all points of the mesh are read in as sets of 3 vertices
	*/
	Assimp::Importer importer;
	const aiScene* mesh_scene = importer.ReadFile(file_path, 
		aiProcess_CalcTangentSpace 
		| aiProcess_Triangulate 
		| aiProcess_JoinIdenticalVertices 
		| aiProcess_SortByPType);
	if (mesh_scene == nullptr)
	{
		throw std::exception("Failed to load mesh file");
	}

	/*
	* Loop through all meshes in the imported scene.
	*/
	for (int mesh_loop_index = 0; mesh_loop_index < mesh_scene->mNumMeshes; mesh_loop_index++)
	{
		aiMesh* current_mesh = mesh_scene->mMeshes[mesh_loop_index];
		int number_of_mesh_faces = current_mesh->mNumFaces;

		/*
		* Loop through all mesh faces
		*/
		for (int face_loop_counter = 0; face_loop_counter < number_of_mesh_faces; face_loop_counter++)
		{
			/*
			* Each face has 3 vertices (triangulated)
			*/
			const aiFace& current_face = current_mesh->mFaces[face_loop_counter];
			for (int vertex_counter = 0; vertex_counter < 3; vertex_counter++)
			{
				//Grab the position vector
				aiVector3D position_vector = current_mesh->mVertices[current_face.mIndices[vertex_counter]];
				Vertex a_vertex;
				a_vertex.m_position.x = position_vector.x;
				a_vertex.m_position.y = position_vector.y;
				a_vertex.m_position.z = position_vector.z;

				//Grab the normal vector
				aiVector3D normal_vector = current_mesh->mVertices[current_face.mIndices[vertex_counter]];
				a_vertex.m_normal.x = normal_vector.x;
				a_vertex.m_normal.y = normal_vector.y;
				a_vertex.m_normal.z = normal_vector.z;

				//Grab the texture coordinates
				aiVector3D texture_coordinates = current_mesh->mTextureCoords[0][current_face.mIndices[vertex_counter]];
				a_vertex.m_texture_coordinate.x = texture_coordinates.x;
				a_vertex.m_texture_coordinate.y = texture_coordinates.y;

				final_vertices.push_back(a_vertex);
			}
		}
	}

	return final_vertices;
}