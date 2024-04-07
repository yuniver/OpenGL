#include "Buffer.h"
#include "RendererAPI.h"
#include "Renderer.h"
#include "../RenderImplement/OpenGL/OpenGLBuffer.h"
namespace Terric
{
	Ref<VertexBuffer> VertexBuffer::Create(uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: return nullptr;
			case RendererAPI::API::OpenGL: return CreateRef<OpenGLVertexBuffer>(size);
		}

		return nullptr;
	}

	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: return nullptr;
		case RendererAPI::API::OpenGL: return CreateRef<OpenGLVertexBuffer>(vertices, size);
		}

		return nullptr;
	}


	
	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    return nullptr;
			case RendererAPI::API::OpenGL:  return CreateRef<OpenGLIndexBuffer>(indices, size);
		}

		return nullptr;
	}
}