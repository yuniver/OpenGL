#include "OpenGLWindow.h"
#include "OpenGLContext.h"
#include "../../Renderer/Camera.h"

namespace Terric
{
	bool OpenGLWindow::Init(const WindowProps& props)
	{
		/* Initialize the library */
		if (!glfwInit())
		{
			std::cout << "Failed to initialize GLFW" << std::endl;
			return false;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //����ģʽ �޷�ʹ��������Ⱦģʽ
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);//�������� ���ɸı��С

		m_window = glfwCreateWindow(props.Width, props.Height, props.Title.c_str(), NULL, NULL);
		if (!m_window)
		{
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
			m_Running = false;
			return false;
		}
		m_Width = props.Width;
		m_Height = props.Height;

		m_Context = new OpenGLContext(m_window);
		m_Context->Init();
		m_Running = true;

		camera.UpdateProjection(glm::radians(45.0f), (float)m_Width / (float)m_Height, 0.1f, 100.0f);

		glViewport(0, 0, m_Width, m_Height); //�̶����ڴ�С�󣬲��ûص���ֱ�������ӿڴ�С

		return true;
	}
	void OpenGLWindow::OnUpdate()
	{
		//ͳ��֡���ʱ��
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;

		ShowErrorMessage(glGetError());
		m_Context->SwapBuffers();
		glfwPollEvents();
	}
	void OpenGLWindow::ProcessInput()
	{
		if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			m_Running = false;
		}

		if (glfwGetKey(m_window, GLFW_KEY_UP) == GLFW_PRESS ||
			glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
		{
			camera.ProcessKeyboard(FORWARD, deltaTime);
		}

		if (glfwGetKey(m_window, GLFW_KEY_DOWN) == GLFW_PRESS ||
			glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
		{
			camera.ProcessKeyboard(BACKWARD, deltaTime);
		}

		if (glfwGetKey(m_window, GLFW_KEY_LEFT) == GLFW_PRESS ||
			glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
		{
			camera.ProcessKeyboard(LEFT, deltaTime);
		}

		if (glfwGetKey(m_window, GLFW_KEY_RIGHT) == GLFW_PRESS ||
			glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
		{
			camera.ProcessKeyboard(RIGHT, deltaTime);
		}
	}
	bool OpenGLWindow::IsRunning()
	{
		return m_Running;
	}

	void OpenGLWindow::ShutDown()
	{
		glfwDestroyWindow(m_window);
	}
	void* OpenGLWindow::GetInstance()
	{
		return m_window;
	}

	void OpenGLWindow::ShowErrorMessage(GLenum errorCode)
	{
		if (errorCode == GL_NO_ERROR)
		{
			return;
		}
		switch (errorCode)
		{
		case GL_INVALID_ENUM:
			std::cout << "GL_INVALID_ENUM" << std::endl;
			break;
		case GL_INVALID_VALUE:
			std::cout << "GL_INVALID_VALUE" << std::endl;
			break;
		case GL_INVALID_OPERATION:
			std::cout << "GL_INVALID_OPERATION" << std::endl;
			break;
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			std::cout << "GL_INVALID_FRAMEBUFFER_OPERATION" << std::endl;
			break;
		case GL_OUT_OF_MEMORY:
			std::cout << "GL_OUT_OF_MEMORY" << std::endl;
			break;
		default:
			std::cout << "UNKONWN" << std::endl;
			break;
		}
	}
}