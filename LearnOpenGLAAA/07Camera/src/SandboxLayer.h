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

	GLuint m_VAO, m_VBO, m_IBO, m_Texture[2];

	float m_Fov = 45.0f;

	float m_Width = 800.0f;
	float m_Height = 600.0f;

	float m_ViewX = 0.0f;
	float m_ViewY = 0.0f;
	float m_ViewZ = -3.0f;

	std::vector<glm::vec3> m_CubePositions = {
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
};