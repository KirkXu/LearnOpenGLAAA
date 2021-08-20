#include "SandboxLayer.h"
#include "glfw/include/GLFW/glfw3.h"

using namespace GLCore;
using namespace GLCore::Utils;

SandboxLayer::SandboxLayer()
{
}

SandboxLayer::~SandboxLayer()
{
}


void SandboxLayer::OnAttach()
{
	EnableGLDebugging();
	// Init here
	m_Shader.push_back(Shader::FromGLSLTextFiles(
		"assets/shaders/14.1.models.vs.glsl",
		"assets/shaders/14.1.models.fs.glsl"
	));
	/*m_Shader.push_back(Shader::FromGLSLTextFiles(
		"assets/shaders/8.1.light_cube.vs.glsl",
		"assets/shaders/8.1.light_cube.fs.glsl"
	));*/

	m_Shader[0]->use();

	glEnable(GL_DEPTH_TEST);
}

void SandboxLayer::OnDetach()
{
	// Shutdown here
	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_IBO);
	for (auto m : m_Shader)
	{
		glDeleteShader(m->GetRendererID());
	}
}

void SandboxLayer::OnEvent(Event& event)
{
	// Events here
	EventDispatcher dispatcher(event);
	dispatcher.Dispatch<KeyPressedEvent>(
		[&](KeyPressedEvent& e)
		{
			if (e.GetKeyCode() == 'W')
				m_Camera.m_Position += m_Camera.m_MovementSpeed * m_Camera.m_Front;
			if (e.GetKeyCode() == 'S')
				m_Camera.m_Position -= m_Camera.m_MovementSpeed * m_Camera.m_Front;
			if (e.GetKeyCode() == 'A')
				m_Camera.m_Position -= glm::normalize(glm::cross(m_Camera.m_Front, m_Camera.m_Up)) * m_Camera.m_MovementSpeed;
			if (e.GetKeyCode() == 'D')
				m_Camera.m_Position += glm::normalize(glm::cross(m_Camera.m_Front, m_Camera.m_Up)) * m_Camera.m_MovementSpeed;
			if (e.GetKeyCode() == 'R')
				m_Camera.m_Front = glm::vec3(0.0f, 0.0f, -1.0f);
			if (e.GetKeyCode() == 'Q')
				m_Camera.m_Position.y += m_Camera.m_MovementSpeed;
			if (e.GetKeyCode() == 'E')
				m_Camera.m_Position.y -= m_Camera.m_MovementSpeed;
			return false;
		});
	dispatcher.Dispatch<MouseMovedEvent>(
		[&](MouseMovedEvent& e)
		{
			
			if (m_FirstMouse) {
				m_LastX = e.GetX();
				m_LastY = e.GetY();
				m_FirstMouse = false;
			}

			float xoffset = e.GetX() - m_LastX;
			float yoffset = m_LastY - e.GetY();
			
			m_LastX = e.GetX();
			m_LastY = e.GetY();

			m_Camera.ProcessMouseMovement(xoffset, yoffset);
			
			return false;
		});

	dispatcher.Dispatch<MouseScrolledEvent>(
		[&](MouseScrolledEvent& e)
		{
			m_Camera.ProcessMouseScroll(e.GetYOffset());
			
			return false;
		});
}

void SandboxLayer::OnUpdate(Timestep ts)
{
	// Render here
	glClearColor(m_BackColor.x, m_BackColor.y, m_BackColor.z, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//LOG_INFO(m_Container01Tex->GetRendererID());

	
	float currentFrame = glfwGetTime();
	m_DeltaTime		   = currentFrame - m_LastFrame;
	m_LastFrame		   = currentFrame;
	m_Camera.m_MovementSpeed = m_SpeedFactor* m_DeltaTime;

	// get matrix's uniform location and set matrix
	m_Shader[0]->use();
	
	// create transformations
	glm::mat4 model      = glm::mat4(1.0f);
	glm::mat4 view       = m_Camera.GetViewMatrix();
	glm::mat4 projection = glm::perspective(glm::radians(m_Camera.m_Zoom), m_Width / m_Height, 0.1f, 100.0f);

	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down

	// pass them to the shaders
	m_Shader[0]->setMat4("model", model);
	m_Shader[0]->setMat4("view", view);
	m_Shader[0]->setMat4("projection", projection);

	m_Model.Draw(*m_Shader[0]);
}

void SandboxLayer::OnImGuiRender()
{
	// ImGui here
	ImGui::Begin("Controls");
	ImGui::SliderFloat("Zoom:", &m_Camera.m_Zoom, 0.0f, 180.0f);
	ImGui::SliderFloat("Width: ", &m_Width, 0.0f, 1280.0f);
	ImGui::SliderFloat("Height: ", &m_Height, 0.0f, 720.0f);


	ImGui::Text(" ");
	ImGui::SliderFloat("SpeedFactor:", &m_SpeedFactor, 0.0f, 20.0f);
	ImGui::Text("Camera Pos");
	ImGui::Text("x: %.1f", m_Camera.m_Position.x);
	ImGui::Text("y: %.1f", m_Camera.m_Position.y);
	ImGui::Text("z: %.1f", m_Camera.m_Position.z);

	ImGui::Text(" ");
	ImGui::Text("Shininess");
	ImGui::SliderFloat("Shininess: ", &m_Shininess, 0.0f, 512.0f);
	ImGui::Text(" ");

	ImGui::ColorEdit3("Back Ground Color", (float*)&m_BackColor);
	ImGui::Text(" ");


	ImGui::End();
}
