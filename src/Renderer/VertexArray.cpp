#include "VertexArray.h"
#include "RendererAPI.h"
#include "../RenderImplement/OpenGL/OpenGLVertexArray.h"

namespace Terric
{
	Ref<VertexArray> VertexArray::Create()
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None:    return nullptr;
		case RendererAPI::API::OpenGL:  return CreateRef<OpenGLVertexArray>();
		}

		return nullptr;
	}
}