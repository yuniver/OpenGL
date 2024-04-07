#pragma once
#include "Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Terric
{
	class OpenGLCamera : public Camera
	{
	public:
		glm::vec3 Position;
		glm::vec3 Front;
		glm::vec3 Up;
		glm::vec3 Right;
		glm::vec3 Worldup;
	public:

		OpenGLCamera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
			//: Camera(posX, posY, posZ, upX, upY, upZ, yaw, pitch)
			: Front(glm::vec3(0.0f, 0.0f, -1.0f)), 
			Position(glm::vec3(posX, posY, posZ)), 
			Worldup(glm::vec3(upX, upY, upZ))
		{
			Speed = SPEED;
			Sensitivity = SENSITIVITY;
			Zoom = ZOOM;
			Yaw = yaw;
			Pitch = pitch;

			updateCameraVecotrs();
		}

		glm::mat4 GetView();
		virtual void ProcessKeyBoard(ECameraMovement dir, float deltaTime) override;
	protected:
		virtual void updateCameraVecotrs() override;
	};
}