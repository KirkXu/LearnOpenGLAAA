#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace GLCore::Utils {
	//
	enum class Camera_Movement {
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT
	};

	// default camera values
	const float YAW         = -90.0f;
	const float PITCH       = 0.0f;
	const float SPEED       = 2.5f;
	const float SENSITIVITY = 0.1f;
	const float ZOOM        = 45.0f;

	class FPSCamera {
	public:
		// constructor with vectors
		FPSCamera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f),
			glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
			float yaw = YAW,
			float pitch = PITCH) :
			m_Front(glm::vec3(0.0f, 0.0f, -1.0f)),
			m_MovementSpeed(SPEED),
			m_MouseSensitivity(SENSITIVITY),
			m_Zoom(ZOOM)
		{
			m_Position = position;
			m_WorldUp = up;
			m_Yaw = yaw;
			m_Pitch = pitch;
			updateCameraVectors();
		}

		// constructor with scalar values
		FPSCamera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) :
			m_Front(glm::vec3(0.0f, 0.0f, -1.0f)),
			m_MovementSpeed(SPEED),
			m_MouseSensitivity(SENSITIVITY),
			m_Zoom(ZOOM)
		{
			m_Position = glm::vec3(posX, posY, posZ);
			m_WorldUp = glm::vec3(upX, upY, upZ);
			m_Yaw = yaw;
			m_Pitch = pitch;
			updateCameraVectors();
		}

		glm::mat4 GetViewMatrix();

		void ProcessKeyboard(Camera_Movement direction, float deltaTime);

		void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);

		void ProcessMouseScroll(float yoffset);

	public:
		// camera attributes
		glm::vec3 m_Position;
		glm::vec3 m_Front;
		glm::vec3 m_Up;
		glm::vec3 m_Right;
		glm::vec3 m_WorldUp;
		// ealer angles
		float m_Yaw;
		float m_Pitch;
		// camera options
		float m_MovementSpeed;
		float m_MouseSensitivity;
		float m_Zoom;

	private:
		// calculate th front vector from the Camera's (updated) Euler Angles
		void updateCameraVectors();

		

	};



}