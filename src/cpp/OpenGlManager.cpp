#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <assert.h>
#include "OpenGlManager.h"
#include "Shader.h"

int OpenGlManager::InitOpenGl()
{
	/* Initialize the library */
	if (!glfwInit())
	{
		std::cout << "Failed to initialize GLFW" << std::endl;
		return -1;
	}

	//版本设置
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //核心模式 无法使用立即渲染模式
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);//窗口设置 不可改变大小

	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Hello World", NULL, NULL);

	if (!window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	//初始化glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}


	//Shader shader(GetVertexShader(), GetFragmentShader());
	Shader shader("Assets/shader/Basic.shader");

	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	Prepare();

	while (!glfwWindowShouldClose(window))
	{
		//统计帧间隔时间
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;

		Update();
		LateUpdate();
		/* 渲染 */
		OnRender();
		glClear(GL_COLOR_BUFFER_BIT);

		//shader.use();

		ShowErrorMessage(glGetError());
		/* 交换前后图像缓冲区 */
		glfwSwapBuffers(window);

		/* 处理所有事件 */
		glfwPollEvents();
	}
	OnDestroy();
	glfwTerminate();

	return 0;
}

void OpenGlManager::processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS ||
		glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera.ProcessKeyboard(FORWARD, deltaTime);
	}

	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS ||
		glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	}

	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS ||
		glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera.ProcessKeyboard(LEFT, deltaTime);
	}

	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS ||
		glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera.ProcessKeyboard(RIGHT, deltaTime);
	}
}

const char* OpenGlManager::GetVertexShader()
{
	return "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";
}

const char* OpenGlManager::GetFragmentShader()
{
	return "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\n\0";
}

void OpenGlManager::ShowErrorMessage(GLenum errorCode)
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

void OpenGlManager::Prepare()
{
	//创建VBO
	unsigned int vbo = 0;
	glGenBuffers(1, &vbo);
}

void OpenGlManager::Update()
{
	//input
	processInput(window);
}

void OpenGlManager::LateUpdate()
{

}

void OpenGlManager::OnRender()
{
}

void OpenGlManager::OnDestroy()
{
}