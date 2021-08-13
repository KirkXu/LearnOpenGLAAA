#include "glpch.h"
#include "FPSCamera.h"

namespace GLCore::Utils {
	

	glm::mat4 FPSCamera::GetViewMatrix()
	{
		return glm::lookAt(m_Position, m_Position + m_Front, m_Up);
	}

	void FPSCamera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
	{
		float velocity = m_MovementSpeed * deltaTime;
		if (direction == Camera_Movement::FORWARD)
			m_Position += m_Front * velocity;
		if (direction == Camera_Movement::BACKWARD)
			m_Position -= m_Front * velocity;
		if (direction == Camera_Movement::LEFT)
			m_Position -= m_Right * velocity;
		if (direction == Camera_Movement::RIGHT)
			m_Position += m_Right * velocity;
	}

	void FPSCamera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch)
	{
		xoffset *= m_MouseSensitivity;
		yoffset *= m_MouseSensitivity;

		m_Yaw += xoffset;
		m_Pitch += yoffset;

		if (constrainPitch)
		{
			if (m_Pitch > 89.0f)
				m_Pitch = 89.0f;
			if (m_Pitch < -89.0f)
				m_Pitch = -89.0f;
		}

		updateCameraVectors();
	}

	void FPSCamera::ProcessMouseScroll(float yoffset)
	{
		m_Zoom -= (float)yoffset;
		if (m_Zoom < 1.0f)
			m_Zoom = 1.0f;
		if (m_Zoom > 45.0f)
			m_Zoom = 45.0f;

		updateCameraVectors();
	}

	void FPSCamera::updateCameraVectors()
	{
		glm::vec3 front;
		front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		front.y = sin(glm::radians(m_Pitch));
		front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		m_Front = glm::normalize(front);

		m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
		m_Up    = glm::normalize(glm::cross(m_Right, m_Front));
	}

}
