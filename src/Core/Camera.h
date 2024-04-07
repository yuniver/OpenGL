#pragma once

namespace Terric
{
	enum ECameraMovement {
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT
	};

	const float YAW = -90.0f;
	const float PITCH = 0.0;
	const float SPEED = 2.5f;
	const float SENSITIVITY = 0.1f;
	const float ZOOM = 45.0f;

	class Camera
	{
	public:
		float Yaw;
		float Pitch;
		float Speed;
		float Sensitivity;
		float Zoom;

		//Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);
		
		void ProcessMouseMovement(float xOffset, float yOffset, bool constrainPitch = true);
		void ProcessScroll(float yOffset);
		virtual void ProcessKeyBoard(ECameraMovement dir, float deltaTime) = 0;
	protected:
		virtual void updateCameraVecotrs() = 0;
	};
}