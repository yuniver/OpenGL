#include "OpenGLMesh.h"
#include "OpenGLModel.h"
#include "OpenGLTexture.h"

#include <glad/glad.h> 
#include <stb_image.h>

#include <iostream>
namespace Terric
{
	OpenGLMesh OpenGLModel::processMesh(aiMesh* mesh, const aiScene* scene)
	{
		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;
		std::vector<Texture> textures;

		for (unsigned int i = 0; i < mesh->mNumVertices; i++)
		{
			Vertex vertex;
			glm::vec3 vector;

			vector.x = mesh->mVertices[i].x;
			vector.y = mesh->mVertices[i].y;
			vector.z = mesh->mVertices[i].z;
			vertex.Position = vector;

			if (mesh->HasNormals())
			{
				vector.x = mesh->mNormals[i].x;
				vector.y = mesh->mNormals[i].y;
				vector.z = mesh->mNormals[i].z;
				vertex.Normal = vector;
			}

			if (mesh->mTextureCoords[0])
			{
				glm::vec2 vec;
				vec.x = mesh->mTextureCoords[0][i].x;
				vec.y = mesh->mTextureCoords[0][i].y;
				vertex.TexCoords = vec;
				//
			}
		}

		return OpenGLMesh(vertices, indices, textures);
	}


	void OpenGLModel::processNode(aiNode* node, const aiScene* scene)
	{
		for (unsigned int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			m_meshes.push_back(processMesh(mesh, scene));
		}

		for (unsigned int i = 0; i < node->mNumChildren; i++)
		{
			processNode(node->mChildren[i], scene);
		}
	}
	std::vector<Texture> OpenGLModel::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
	{
		std::vector<Texture> textures;
		for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
		{
			aiString str;
			mat->GetTexture(type, i, &str);
			bool skip = false;
			for (unsigned int j = 0; j < m_textures.size(); j++)
			{
				if (std::strcmp(m_textures[j].path.data(), str.C_Str()) == 0)
				{
					textures.push_back(m_textures[j]);
					skip = true;
					break;
				}
			}
			if (!skip)
			{
				Texture texture;
				texture.id = OpenGLTexture::LoadTexture(str.C_Str(), m_directory);
				texture.type = typeName;
				texture.path = str.C_Str();
				textures.push_back(texture);
				m_textures.push_back(texture);
			}
		}
		return textures;
	}
	//uint32_t OpenGLModel::textureFromFile(const char* path, const std::string directory)
	//{
	//	std::string filename = std::string(path);
	//	filename = directory + '/' + filename;

	//	unsigned int textureID;
	//	glGenTextures(1, &textureID);
	//	int width, height, nrComponents;
	//	unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);

	//	if (!data)
	//	{
	//		std::cout << "Texture failed to load at path: " << path << std::endl;
	//		stbi_image_free(data);
	//		return textureID;
	//	}

	//	unsigned int format;
	//	if (nrComponents == 1)
	//		format = GL_RED;
	//	else if (nrComponents == 3)
	//		format = GL_RGB;
	//	else if (nrComponents == 4)
	//		format = GL_RGBA;

	//	glBindTexture(GL_TEXTURE_2D, textureID);
	//	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	//	glGenerateMipmap(GL_TEXTURE_2D);

	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//	stbi_image_free(data);
	//	return textureID;
	//}
}