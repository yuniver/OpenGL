
#include "GraphicsContext.h"
#include "Renderer.h"
#include "../RenderImplement/OpenGL/OpenGLContext.h"

namespace Terric
{
	Scope<GraphicsContext> GraphicsContext::Create(void* window)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    return nullptr;
		case RendererAPI::API::OpenGL:  return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
		}

		return nullptr;
	}
}
