#pragma once
#include "Mesh.h"

namespace Terric
{

	class OpenGLMesh : public Mesh
	{
	public:
		OpenGLMesh()
		{
			cubeVAO = 0;
			cubeVBO = 0;
			planeVAO = 0;
			planeVBO = 0;
			quadVAO = 0;
			quadVBO = 0;
		}

		OpenGLMesh(std::vector<Vertex>vertices, std::vector<uint32_t> indices, std::vector<Texture> textures)
		{
			m_vertices = vertices;
			m_indices = indices;
			m_textures = textures;
			setupMesh();
		}
		virtual void Draw(Shader& shader) override;
		
		void RenderTestBatch(const Shader& shader, unsigned int planeVAO);
		void ReleaseTestScene();
		unsigned int GenCube();
		unsigned int GenPlane();
		unsigned int GenQuad();
	public:
		unsigned int cubeVAO;
		unsigned int cubeVBO;
		unsigned int planeVAO;
		unsigned int planeVBO;
		unsigned int quadVAO;
		unsigned int quadVBO;
	protected:
		virtual void setupMesh() override;
	};
}