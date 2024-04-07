#pragma once
#include "../../Renderer/GraphicsContext.h"


namespace Terric
{
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle) 
			: m_WindowHandle(windowHandle) { }

		virtual bool Init() override;
		virtual void SwapBuffers() override;

	private:
		GLFWwindow* m_WindowHandle;
	};
}