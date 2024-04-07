#include "Renderer.h"

namespace Terric
{
	void Renderer::Init()
	{
		RenderCommand::Init();
	}

	void Renderer::Shutdown()
	{
	}
	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
	}
	void Renderer::BeginScene(Camera& camera)
	{
		//s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}
	void Renderer::EndScene()
	{
	}
	void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform)
	{
		shader->Bind();
		//shader->setMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
		shader->setMat4("u_Transform", transform);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}
