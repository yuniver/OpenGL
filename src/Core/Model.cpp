#include "Model.h"
#include <iostream>

namespace Terric
{
	void Model::loadModel(std::string path)
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_NON_VERBOSE_FORMAT || !scene->mRootNode)
		{
			std::cout << "Error! ASSIMP:" << importer.GetErrorString() << std::endl;
			return;
		}

		m_directory = path.substr(0, path.find_last_of('/'));
		processNode(scene->mRootNode, scene);
	}
}