#include "SandboxLayer.h"
#include "stb_image/stb_image.h"
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
		"assets/shaders/8.1.colors.vs.glsl",
		"assets/shaders/8.1.colors.fs.glsl"
	));
	m_Shader.push_back(Shader::FromGLSLTextFiles(
		"assets/shaders/8.1.light_cube.vs.glsl",
		"assets/shaders/8.1.light_cube.fs.glsl"
	));

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
	-0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f, -0.5f,
	 0.5f,  0.5f, -0.5f,
	 0.5f,  0.5f, -0.5f,
	-0.5f,  0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,
						
	-0.5f, -0.5f,  0.5f,
	 0.5f, -0.5f,  0.5f,
	 0.5f,  0.5f,  0.5f,
	 0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,
	-0.5f, -0.5f,  0.5f,
						
	-0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,
						
	 0.5f,  0.5f,  0.5f,
	 0.5f,  0.5f, -0.5f,
	 0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f,  0.5f,
	 0.5f,  0.5f,  0.5f,
						
	-0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f,  0.5f,
	 0.5f, -0.5f,  0.5f,
	-0.5f, -0.5f,  0.5f,
	-0.5f, -0.5f, -0.5f,
						
	-0.5f,  0.5f, -0.5f,
	 0.5f,  0.5f, -0.5f,
	 0.5f,  0.5f,  0.5f,
	 0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f, -0.5f
	};

	glGenVertexArrays(1, &m_CubeVAO);
	glGenBuffers(1, &m_VBO);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	glBindVertexArray(m_CubeVAO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	
	glGenVertexArrays(1, &m_LightCubeVAO);
	glBindVertexArray(m_LightCubeVAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

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
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// bind Texture
	
	float currentFrame = glfwGetTime();
	m_DeltaTime		   = currentFrame - m_LastFrame;
	m_LastFrame		   = currentFrame;
	m_Camera.m_MovementSpeed = m_SpeedFactor* m_DeltaTime;

	// get matrix's uniform location and set matrix
	m_Shader[0]->use();
	m_Shader[0]->setVec3("objectColor", 1.0f, 0.5f, 0.31f);
	m_Shader[0]->setVec3("lightColor", 1.0f, 1.0f, 1.0f);
	
	// create transformations
	glm::mat4 model      = glm::mat4(1.0f);
	glm::mat4 view       = m_Camera.GetViewMatrix();
	glm::mat4 projection = glm::perspective(glm::radians(m_Camera.m_Zoom), m_Width / m_Height, 0.1f, 100.0f);

	// pass them to the shaders
	m_Shader[0]->setMat4("model", model);
	m_Shader[0]->setMat4("view", view);
	m_Shader[0]->setMat4("projection", projection);

	glBindVertexArray(m_CubeVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	// draw the lamp object
	m_Shader[1]->use();
	model = glm::mat4(1.0f);
	model = glm::translate(model, m_LightPos);
	model = glm::scale(model, glm::vec3(0.2f));
	m_Shader[1]->setMat4("model", model);
	m_Shader[1]->setMat4("view", view);
	m_Shader[1]->setMat4("projection", projection);

	glBindVertexArray(m_LightCubeVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void SandboxLayer::OnImGuiRender()
{
	// ImGui here
	ImGui::Begin("Controls");
	ImGui::SliderFloat("Zoom:", &m_Camera.m_Zoom, 0.0f, 180.0f);
	ImGui::SliderFloat("Width: ", &m_Width, 0.0f, 1280.0f);
	ImGui::SliderFloat("Height: ", &m_Height, 0.0f, 720.0f);

	ImGui::Text(" ");
	ImGui::Text("m_FirstMouse: %d", m_FirstMouse);

	ImGui::Text(" ");
	ImGui::SliderFloat("SpeedFactor:", &m_SpeedFactor, 0.0f, 20.0f);
	ImGui::Text("Camera Pos");
	ImGui::Text("x: %.1f", m_Camera.m_Position.x);
	ImGui::Text("y: %.1f", m_Camera.m_Position.y);
	ImGui::Text("z: %.1f", m_Camera.m_Position.z);

	ImGui::Text("Camera Front: %.1f, %.1f, %.1f", m_Camera.m_Front.x, m_Camera.m_Front.y, m_Camera.m_Front.z);
	
	ImGui::Text(" ");
	ImGui::Text("m_Yaw: %.1f", m_Camera.m_Yaw);
	ImGui::Text("m_Pitch: %.1f", m_Camera.m_Pitch);
	ImGui::Text("m_LastX: %.1f", m_LastX);
	ImGui::Text("m_LastY: %.1f", m_LastY);


	ImGui::Text(" ");
	ImGui::Text("aspect-ration: %.1f", m_Width / m_Height);
	ImGui::End();
}
