#pragma once
#include "Base.h"

namespace Terric
{
	class GraphicsContext
	{
	public:
		virtual ~GraphicsContext() = default;

		virtual bool Init() = 0;
		virtual void SwapBuffers() = 0;

		static Scope<GraphicsContext> Create(void* window);
	};
}