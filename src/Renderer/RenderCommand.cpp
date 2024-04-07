#include "RenderCommand.h"

namespace Terric
{
	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();
}
