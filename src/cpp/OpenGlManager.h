#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Camera.h"

class OpenGlManager
{
	//窗口设置
	const float cameraSpeed = 0.05f;
	unsigned int SCR_WIDTH = 800;
	unsigned int SCR_HEIGHT = 600;

	GLFWwindow* window;
	Camera camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));
	float deltaTime = 0.0f;	//每帧间隔时间
	float lastFrame = 0.0f;
	void processInput(GLFWwindow* window);
	void Prepare();
	void ShowErrorMessage(GLenum errorCode);
public:
	int InitOpenGl();

	const char* GetVertexShader();
	const char* GetFragmentShader();

	
	virtual void Update();
	virtual void LateUpdate();
	virtual void OnRender();
	virtual void OnDestroy();
};
