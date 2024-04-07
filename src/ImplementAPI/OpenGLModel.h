#pragma once
#include "Model.h"

namespace Terric
{
	class OpenGLModel :public Model
	{
	public:
		std::vector<OpenGLMesh> m_meshes;
	protected:
		virtual void processNode(aiNode* node, const aiScene* scene) override;
		//virtual uint32_t textureFromFile(const char* path, const std::string directory) override;
		OpenGLMesh processMesh(aiMesh* mesh, const aiScene* scene);
		virtual std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName) override;
	};
}