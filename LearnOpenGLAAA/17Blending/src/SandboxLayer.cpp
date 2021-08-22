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
		"assets/shaders/17.1.blending_discard.vs.glsl",
		"assets/shaders/17.2.blending_discard.fs.glsl"
	));


	stbi_set_flip_vertically_on_load(true);

	m_CubeTex = std::make_shared<GLCore::Utils::Texture>();
	m_CubeTex->loadTexture("assets/textures/marble.jpg");

	m_FloorTex = std::make_shared<GLCore::Utils::Texture>();
	m_FloorTex->loadTexture("assets/textures/metal.png");

	m_TransparentTex = std::make_shared<GLCore::Utils::Texture>();
	m_TransparentTex->loadTexture("assets/textures/window.png");

	m_Shader[0]->use();
	m_Shader[0]->setInt("texture1", 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// positions          // texture Coords
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	float planeVertices[] = {
		// positions          // texture Coords (note we set these higher than 1 (together with GL_REPEAT as texture wrapping mode). this will cause the floor texture to repeat)
		 5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
		-5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
		-5.0f, -0.5f, -5.0f,  0.0f, 2.0f,

		 5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
		-5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
		 5.0f, -0.5f, -5.0f,  2.0f, 2.0f
	};

	float transparentVertices[] = {
		// positions         // texture Coords (swapped y coordinates because texture is flipped upside down)
		0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
		0.0f, -0.5f,  0.0f,  0.0f,  1.0f,
		1.0f, -0.5f,  0.0f,  1.0f,  1.0f,

		0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
		1.0f, -0.5f,  0.0f,  1.0f,  1.0f,
		1.0f,  0.5f,  0.0f,  1.0f,  0.0f
	};

	glGenVertexArrays(1, &m_CubeVAO);
	glGenBuffers(1, &m_CubeVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_CubeVBO);
	glBindVertexArray(m_CubeVAO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glBindVertexArray(0);

	glGenVertexArrays(1, &m_PlaneVAO);
	glGenBuffers(1, &m_PlaneVBO);
	glBindVertexArray(m_PlaneVAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_PlaneVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glBindVertexArray(0);

	glGenVertexArrays(1, &m_TransparentVAO);
	glGenBuffers(1, &m_TransparentVBO);
	glBindVertexArray(m_TransparentVAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_TransparentVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(transparentVertices), transparentVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glBindVertexArray(0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
}

void SandboxLayer::OnDetach()
{
	// Shutdown here
	glDeleteBuffers(1, &m_CubeVBO);
	glDeleteBuffers(1, &m_PlaneVBO);
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
	std::map<float, glm::vec3> sorted;
	for (unsigned int i = 0; i < m_Windows.size(); i++)
	{
		float distance = glm::length(m_Camera.m_Position - m_Windows[i]);
		sorted[distance] = m_Windows[i];
	}

	// Render here
	glClearColor(m_BackColor.x, m_BackColor.y, m_BackColor.z, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//LOG_INFO(m_Container01Tex->GetRendererID());


	float currentFrame = glfwGetTime();
	m_DeltaTime = currentFrame - m_LastFrame;
	m_LastFrame = currentFrame;
	m_Camera.m_MovementSpeed = m_SpeedFactor * m_DeltaTime;



	// draw objects
	m_Shader[0]->use();
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = m_Camera.GetViewMatrix();
	glm::mat4 projection = glm::perspective(glm::radians(m_Camera.m_Zoom), m_Width / m_Height, 0.1f, 100.0f);

	// pass them to the shaders
	m_Shader[0]->setMat4("view", view);
	m_Shader[0]->setMat4("projection", projection);
	m_Shader[0]->use();
	m_Shader[0]->setMat4("model", glm::mat4(1.0f));

	// cubes
	glBindVertexArray(m_CubeVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_CubeTex->GetRendererID());
	model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
	m_Shader[0]->setMat4("model", model);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
	m_Shader[0]->setMat4("model", model);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	// floor
	glBindVertexArray(m_PlaneVAO);
	glBindTexture(GL_TEXTURE_2D, m_FloorTex->GetRendererID());
	model = glm::mat4(1.0f);
	m_Shader[0]->setMat4("model", model);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	// vegetation
	glBindVertexArray(m_TransparentVAO);
	glBindTexture(GL_TEXTURE_2D, m_TransparentTex->GetRendererID());
	m_Shader[0]->setFloat("transFactor", m_TransFactor);
	for (auto it = sorted.rbegin(); it != sorted.rend(); ++it)
	{
		model = glm::mat4(1.0f);
		model = glm::translate(model, it->second);
		m_Shader[0]->setMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

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

	ImGui::End();
}
