#pragma once

#include "Shader.h"
#include <glm/glm.hpp>
#include <vector>
#include <string>

#define MAX_BONE_INFLUENCE 4

namespace Terric
{
	struct Vertex
	{
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TexCoords;
		glm::vec3 Tangent;
		glm::vec3 Bitangent;

		int m_BoneIDs[MAX_BONE_INFLUENCE];
		float m_Weights[MAX_BONE_INFLUENCE];
	};
	struct Texture
	{
		unsigned int id;
		std::string type;
		std::string path;
	};

	class Mesh
	{
	public:
		std::vector<Vertex> m_vertices;
		std::vector<uint32_t> m_indices;
		std::vector<Texture> m_textures;
		unsigned int VAO;

		virtual void Draw(Shader& shader) = 0;
	protected:
		unsigned int VBO, EBO;
		virtual void setupMesh() = 0;
	};
}