#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Camera.h"


class Shadow
{
	//窗口设置
	float scaleFactor = 1.0f;
	const float cameraSpeed = 0.05f;
	unsigned int SCR_WIDTH = 800 * scaleFactor;
	unsigned int SCR_HEIGHT = 600 * scaleFactor;

	GLFWwindow* window;
	Camera camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));
	float deltaTime = 0.0f;	//每帧间隔时间
	float lastFrame = 0.0f;
	void processInput(GLFWwindow* window);
public:
	int InitOpenGl();

	virtual const char* GetVertexShader();
	virtual const char* GetFragmentShader();

	virtual void Awake();
	virtual void Update();
	virtual void LateUpdate();
	virtual void OnRender();
	virtual void OnDestroy();
};
