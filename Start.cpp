#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "src/ImplementAPI/OpenGLCamera.h"
#include "src/ImplementAPI/OpenGLTexture.h"
#include "src/ImplementAPI/OpenGLMesh.h"
#include "src/ImplementAPI/OpenGLRenderCMD.h"
//#include "src/ImplementAPI/OpenGLWindow.h"
#include "Model.h"

#include <iostream>

using namespace Terric;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

OpenGLCamera camera(0.0f, 0.0f, 3.0f, 0.0f, 1.0f, 0.0f, YAW, PITCH);
// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
float lastX = (float)SCR_WIDTH / 2.0;
float lastY = (float)SCR_HEIGHT / 2.0;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;


int main()
{
	// meshes
	unsigned int planeVAO;
	unsigned int quadVAO = 0;
	OpenGLRenderCMD::Init();

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif


	//OpenGLWindow window = OpenGLWindow(SCR_WIDTH, SCR_HEIGHT, "ShadowMap Test");
	//if (window.Init() == -1)
	//	return -1;

	//window.SetCamera(camera);
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glEnable(GL_DEPTH_TEST);

	// build and compile shaders
	// -------------------------
	Shader BasicShadowMap("Assets/shader/shadow_mapping.shader");
	Shader DepthTexShader("Assets/shader/shadow_mapping_depth.shader");
	Shader debugDepthQuad("Assets/shader/debug_quad_depth.shader");
	
	OpenGLMesh mesh = OpenGLMesh();

	planeVAO = mesh.GenPlane();
	unsigned int wallTex = OpenGLTexture::LoadTexture("wall.jpg", "Assets/textures");

	//Depth Map Framebuffer
	const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
	unsigned int depthMapFBO, depthMap;
	depthMap = OpenGLTexture::GenTexture(SHADOW_WIDTH, SHADOW_HEIGHT);
	OpenGLRenderCMD::CreateFrameBuffer(depthMapFBO, depthMap);

	// shader configuration
	// --------------------
	BasicShadowMap.Bind();
	uint32_t diffuseTexIndex = 0, shadowMapTexIndex = 1;
	BasicShadowMap.setInt("diffuseTexture", diffuseTexIndex);
	BasicShadowMap.setInt("shadowMap", shadowMapTexIndex);
	debugDepthQuad.Bind();
	debugDepthQuad.setInt("depthMap", 0);

	// lighting info
	// -------------
	glm::vec3 lightPos(-2.0f, 4.0f, -1.0f);

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		//window.ProcessInput();
		processInput(window);

		// change light position over time
		lightPos.x = sin(glfwGetTime()) * 3.0f;
		lightPos.z = cos(glfwGetTime()) * 2.0f;
		lightPos.y = 5.0 + cos(glfwGetTime()) * 1.0f;

		// render
		OpenGLRenderCMD::SetClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		
		//PASS 1 渲染深度图
		OpenGLRenderCMD::Clear(COLOR_CLEAR | DEPTH_CLEAR);
		OpenGLRenderCMD::SetView(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);


		glm::mat4 lightProjection, lightView;
		glm::mat4 lightSpaceMatrix;
		float near_plane = 1.0f, far_plane = 7.5f;
		//lightProjection = glm::perspective(glm::radians(45.0f), (GLfloat)SHADOW_WIDTH / (GLfloat)SHADOW_HEIGHT, near_plane, far_plane); // note that if you use a perspective projection matrix you'll have to change the light position as the current light position isn't enough to reflect the whole scene
		lightProjection = glm::ortho(-10.0f, 5.0f, -10.0f, 10.0f, near_plane, far_plane);
		lightView = glm::lookAt(lightPos, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
		lightSpaceMatrix = lightProjection * lightView;
		//光源方向渲染深度图
		DepthTexShader.Bind();
		DepthTexShader.setMat4("lightSpaceMatrix", lightSpaceMatrix);

		OpenGLRenderCMD::BindFrameBuffer(depthMapFBO);
		OpenGLRenderCMD::Clear(DEPTH_CLEAR);
		OpenGLRenderCMD::BindTexture(0, wallTex);
		mesh.RenderTestBatch(DepthTexShader, planeVAO);
		OpenGLRenderCMD::UnbindFrameBuffer();
		
		/* */
		//PASS 2 正常渲染
		//重置画布
		OpenGLRenderCMD::Clear(COLOR_CLEAR | DEPTH_CLEAR);
		OpenGLRenderCMD::SetView(0, 0, SCR_WIDTH, SCR_HEIGHT);

		BasicShadowMap.Bind();
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = camera.GetView();
		BasicShadowMap.setMat4("projection", projection);
		BasicShadowMap.setMat4("view", view);
		//light
		BasicShadowMap.setVec3("viewPos", camera.Position);
		BasicShadowMap.setVec3("lightPos", lightPos);
		BasicShadowMap.setMat4("lightSpaceMatrix", lightSpaceMatrix);

		OpenGLRenderCMD::BindTexture(diffuseTexIndex, wallTex);
		OpenGLRenderCMD::BindTexture(shadowMapTexIndex, depthMap);
		mesh.RenderTestBatch(BasicShadowMap, planeVAO);

		// render Depth map to quad for visual debugging
		debugDepthQuad.Bind();
		debugDepthQuad.setFloat("near_plane", near_plane);
		debugDepthQuad.setFloat("far_plane", far_plane);
		OpenGLRenderCMD::BindTexture(0, depthMap);
		if(quadVAO == 0)
			quadVAO = mesh.GenQuad();
		//OpenGLRenderCMD::DrawScreen(quadVAO, 0, 4);

		//window.OnUpdate();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	mesh.ReleaseTestScene();
	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyBoard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyBoard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyBoard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyBoard(RIGHT, deltaTime);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessScroll(static_cast<float>(yoffset));
}