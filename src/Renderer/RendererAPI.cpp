#include "RendererAPI.h"
#include "../RenderImplement/OpenGL/OpenGLRendererAPI.h"

namespace Terric
{
	RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;

	Scope<RendererAPI> Terric::RendererAPI::Create()
	{
		switch (s_API)
		{
		case RendererAPI::API::None:    return nullptr;
		case RendererAPI::API::OpenGL:  return CreateScope<OpenGLRendererAPI>();
		}

		return nullptr;
	}
}