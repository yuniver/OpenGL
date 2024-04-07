#include "Camera.h"

namespace Terric
{

	void Camera::ProcessScroll(float yOffset)
	{
		Zoom -= (float)yOffset;
		if (Zoom < 1.0f)
			Zoom = 1.0f;
		if (Zoom > 45.0f)
			Zoom = 45.0f;
	}
	void Camera::ProcessMouseMovement(float xOffset, float yOffset, bool constrainPitch)
	{
		xOffset *= Sensitivity;
		yOffset *= Sensitivity;

		Yaw += xOffset;
		Pitch += yOffset;

		if (constrainPitch)
		{
			if (Pitch > 89.0f)
				Pitch = 89.0f;
			if (Pitch < -89.0f)
				Pitch = -89.0f;
		}

		updateCameraVecotrs();
	}
}
