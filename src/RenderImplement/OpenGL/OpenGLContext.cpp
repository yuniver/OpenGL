#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "OpenGLContext.h"
#include <iostream>

namespace Terric
{
	bool OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			return false;
		}
		return true;
	}
	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}
