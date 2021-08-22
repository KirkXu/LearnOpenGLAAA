#pragma once

#include <GLCore.h>
#include <GLCoreUtils.h>


class SandboxLayer : public GLCore::Layer
{
public:
	SandboxLayer();
	virtual ~SandboxLayer();

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnEvent(GLCore::Event& event) override;
	virtual void OnUpdate(GLCore::Timestep ts) override;
	virtual void OnImGuiRender() override;
private:
	std::vector<GLCore::Utils::Shader*> m_Shader;

	GLuint m_CubeVAO, m_LightCubeVAO, m_PlaneVAO;
	GLuint m_CubeVBO, m_PlaneVBO;

	float m_Fov = 45.0f;

	float m_Width  = 800.0f;
	float m_Height = 600.0f;

	GLCore::Utils::FPSCamera m_Camera;
	glm::vec3 m_CameraPos   = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 m_CameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 m_CameraUp    = glm::vec3(0.0f, 1.0f, 0.0f);
	float m_CameraSpeed     = 0.05f;
	float m_SpeedFactor     = 2.5f;

	float m_DeltaTime = 0.0f;
	float m_LastFrame = 0.0f;

	float m_LastX = m_Width / 2;
	float m_LastY = m_Height / 2;

	float m_Yaw = 0.0f;
	float m_Pitch = 0.0f;

	bool m_FirstMouse = true;

	glm::vec3 m_LightPos = glm::vec3(1.2f, 1.0f, 2.0f);

	float m_Shininess = 32.0f;

	std::shared_ptr<GLCore::Utils::Texture> m_CubeTex;
	std::shared_ptr<GLCore::Utils::Texture> m_FloorTex;


	std::vector<glm::vec3> cubePositions = {
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

	std::vector<glm::vec3> pointLightPositions = {
		glm::vec3(0.7f,  0.2f,  2.0f),
		glm::vec3(2.3f, -3.3f, -4.0f),
		glm::vec3(-4.0f,  2.0f, -12.0f),
		glm::vec3(0.0f,  0.0f, -3.0f)
	};

	std::vector<glm::vec3> pointLightColor = {
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
	};

	glm::vec3 m_BackColor = glm::vec3(0.0f, 0.0f, 0.0f);
};