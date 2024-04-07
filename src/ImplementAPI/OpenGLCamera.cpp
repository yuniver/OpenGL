#include "OpenGLCamera.h"

#include <glad/glad.h>

namespace Terric
{
	void OpenGLCamera::ProcessKeyBoard(ECameraMovement dir, float deltaTime)
	{
		float velocity = Speed * deltaTime;
		if (dir == FORWARD)
			Position += Front * velocity;
		if (dir == BACKWARD)
			Position -= Front * velocity;
		if (dir == LEFT)
			Position -= Right * velocity;
		if (dir == RIGHT)
			Position += Right * velocity;
	}

	glm::mat4 OpenGLCamera::GetView()
	{
		return glm::lookAt(Position, Position + Front, Up);
	}

	void OpenGLCamera::updateCameraVecotrs()
	{
		glm::vec3 front;

		front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		front.y = sin(glm::radians(Pitch));
		front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));

		
		Front = glm::normalize(front);
		Right = glm::normalize(glm::cross(Front, Worldup));
		Up = glm::normalize(glm::cross(Right, Front));
	}
}