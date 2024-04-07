#include "OpenGLWindow.h"
#include <GLFW/glfw3.h>
#include <iostream>
namespace Terric
{
	//OpenGLWindow::OpenGLWindow(unsigned int width, unsigned int height, const char* name)
	//{
	//	m_width = width;
	//	m_height = height;
	//	m_windowName = name;
	//	m_isRunning = true;
	//	m_window = nullptr;
	//	//camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));
	//}
	//int OpenGLWindow::Init()
	//{
	//	m_window = glfwCreateWindow(m_width, m_height, m_windowName, NULL, NULL);
	//	if (m_window == NULL)
	//	{
	//		std::cout << "Failed to create GLFW window" << std::endl;
	//		glfwTerminate();
	//		return;
	//	}
	//	glfwMakeContextCurrent(m_window);
	//	glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
	//	//glfwSetCursorPosCallback(m_window, mouse_callback);
	//	//glfwSetScrollCallback(m_window, scroll_callback);

	//	// tell GLFW to capture our mouse
	//	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	//	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	//	{
	//		std::cout << "Failed to initialize GLAD" << std::endl;
	//		return -1;
	//	}
	//	glEnable(GL_DEPTH_TEST);
	//	return 1;
	//}


	//void OpenGLWindow::OnUpdate()
	//{
	//	glfwSwapBuffers(m_window);
	//	glfwPollEvents();
	//}

	//void OpenGLWindow::SetCamera(OpenGLCamera& camera)
	//{
	//	m_camera = camera;
	//}

	//bool OpenGLWindow::IsRunning()
	//{
	//	return m_isRunning;
	//}

	//void OpenGLWindow::framebuffer_size_callback(GLFWwindow* window, int width, int height)
	//{
	//	glViewport(0, 0, width, height);
	//}

	//void OpenGLWindow::ProcessInput()
	//{
	//	if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	//	{
	//		glfwSetWindowShouldClose(m_window, true);
	//		m_isRunning = false;
	//	}

	//	if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
	//		m_camera.ProcessKeyBoard(FORWARD, deltaTime);
	//	if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
	//		m_camera.ProcessKeyBoard(BACKWARD, deltaTime);
	//	if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
	//		m_camera.ProcessKeyBoard(LEFT, deltaTime);
	//	if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
	//		m_camera.ProcessKeyBoard(RIGHT, deltaTime);
	//}

	//void OpenGLWindow::mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
	//{
	//	float xpos = static_cast<float>(xposIn);
	//	float ypos = static_cast<float>(yposIn);
	//	if (firstMouse)
	//	{
	//		lastX = xpos;
	//		lastY = ypos;
	//		firstMouse = false;
	//	}

	//	float xoffset = xpos - lastX;
	//	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	//	lastX = xpos;
	//	lastY = ypos;

	//	m_camera.ProcessMouseMovement(xoffset, yoffset);
	//}

	//void OpenGLWindow::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
	//{
	//	m_camera.ProcessScroll(static_cast<float>(yoffset));
	//}

	//void OpenGLWindow::Close()
	//{
	//	glfwTerminate();
	//}
}
