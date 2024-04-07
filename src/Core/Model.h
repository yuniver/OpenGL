#pragma once
#include "Mesh.h"

#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

#include <string>
#include <vector>
namespace Terric
{
	class Model
	{
	public:
		std::vector<Texture> m_textures;
		std::string m_directory;
		bool gammaCorrection;

		Model(std::string const& path, bool gamma = false) : gammaCorrection(gamma)
		{
			loadModel(path.c_str());
		}
	protected:
		virtual void processNode(aiNode* node, const aiScene* scene) = 0;
		/*virtual Mesh processMesh(aiMesh* mesh, const aiScene* scene) = 0;*/
		//virtual uint32_t textureFromFile(const char* path, const std::string directory) = 0;
	protected:
		void loadModel(std::string path);		
		virtual std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName) = 0;
	};
}