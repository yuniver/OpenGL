#include <stb_image.h>
#include <iostream>
#include "Application.h"
#include "../Renderer/RenderCommand.h"
#include "../Renderer/RendererAPI.h"
#include "../Renderer/Shader.h"
#include "../Renderer/Window.h"
#include "../Renderer/Texture.h"
#include "../RenderImplement/OpenGL/OpenGLWindow.h"
#include "../RenderImplement/OpenGL/OpenGLTexture.h"

#include "Base.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../Renderer/Texture.h"

namespace Terric
{
	Application* Application::s_Instance = nullptr;
	void Application::Close()
	{
		m_Running = false;
	}

	int Application::Init()
	{
		OpenGLWindow window = OpenGLWindow();
		WindowProps props;
		props.Width = SCR_WIDTH;
		props.Height = SCR_HEIGHT;
		props.Title = "Terric Test";
		if (!window.Init(props))
			return -1;

		glEnable(GL_DEPTH_TEST);
		Shader shader("Assets/shader/Basic.shader"); //加载shader

		Prepare();
		//顶点
		float vertices[] = {
				-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
				 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
				 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
				 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
				-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
				-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

				-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
				 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
				 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
				 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
				-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
				-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

				-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
				-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
				-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
				-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
				-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
				-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

				 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
				 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
				 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
				 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
				 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
				 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

				-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
				 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
				 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
				 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
				-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
				-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

				-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
				 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
				 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
				 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
				-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
				-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
		};

		glm::vec3 cubePositions[] = {
			glm::vec3(0.0f,  0.0f,  0.0f),
			glm::vec3(2.0f,  5.0f, -15.0f),
			glm::vec3(-1.5f, -2.2f, -2.5f),
			glm::vec3(-3.8f, -2.0f, -12.3f),
			glm::vec3(2.4f, -0.4f, -3.5f),
			glm::vec3(-1.7f,  3.0f, -7.5f),
			glm::vec3(1.3f, -2.0f, -2.5f),
			glm::vec3(1.5f,  2.0f, -2.5f),
			glm::vec3(1.5f,  0.2f, -1.5f),
			glm::vec3(-1.3f,  1.0f, -1.5f)
		};

		unsigned int VBO, VAO;
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		// position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		// texture coord attribute
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		//贴图
		unsigned int texture2;
		auto texture = CreateRef<OpenGLTexture>();
		texture->Load("Assets/textures/wall.jpg", false);

		auto texture1 = CreateRef<OpenGLTexture>();
		texture1->Load("Assets/textures/awesomeface.png",true);

		shader.Bind();
		shader.setInt("texture1", 0);
		shader.setInt("texture2", 1);
		Camera camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));
		camera.UpdateProjection(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		RenderCommand::SetClearColor({ 0.2f, 0.3f, 0.3f, 1.0f });

		while (window.IsRunning())
		{
			window.ProcessInput();
			/* 渲染 */
			RenderCommand::SetClearColor({ 0.2f, 0.3f, 0.3f, 1.0f });
			RenderCommand::Clear();

			texture->Bind(0);
			texture1->Bind(1);

			shader.Bind();
			// Transform
			glm::mat4 view = glm::mat4(1.0f); 
			
			glm::mat4 projection = camera.GetViewProjectionMatrix();
			view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
			shader.setMat4("projection", projection);
			shader.setMat4("view", view);

			// render boxes
			glBindVertexArray(VAO);
			for (unsigned int i = 0; i < 10; i++)
			{
				// calculate the model matrix for each object and pass it to shader before drawing
				glm::mat4 model = glm::mat4(1.0f);
				model = glm::translate(model, cubePositions[i]);
				float angle = 20.0f * i;
				model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
				shader.setMat4("model", model);

				glDrawArrays(GL_TRIANGLES, 0, 36);
			}



			window.OnUpdate();
		}
		window.ShutDown();
		OnDestroy();
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteProgram(shader.ID);
		glfwTerminate();

		return 0;
	}

	//void Application::processInput(GLFWwindow* window)
	//{
	//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	//		glfwSetWindowShouldClose(window, true);

	//	//if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS ||
	//	//	glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	//	//{
	//	//	camera.ProcessKeyboard(FORWARD, deltaTime);
	//	//}

	//	//if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS ||
	//	//	glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	//	//{
	//	//	camera.ProcessKeyboard(BACKWARD, deltaTime);
	//	//}

	//	//if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS ||
	//	//	glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	//	//{
	//	//	camera.ProcessKeyboard(LEFT, deltaTime);
	//	//}

	//	//if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS ||
	//	//	glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	//	//{
	//	//	camera.ProcessKeyboard(RIGHT, deltaTime);
	//	//}
	//}



	void Application::Prepare()
	{

	}

	void Application::OnRender(Shader* shader, unsigned int& VAO)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		shader->Bind();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		//glDrawArrays(GL_LINES, 0, 3);
	}

	void Application::OnDestroy()
	{
	}
}

