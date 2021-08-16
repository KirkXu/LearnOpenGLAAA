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
		"assets/shaders/12.3.light_casters.vs.glsl",
		"assets/shaders/12.3.light_casters.fs.glsl"
	));
	m_Shader.push_back(Shader::FromGLSLTextFiles(
		"assets/shaders/8.1.light_cube.vs.glsl",
		"assets/shaders/8.1.light_cube.fs.glsl"
	));

	stbi_set_flip_vertically_on_load(true);

	m_ContainerTex = std::make_shared<GLCore::Utils::Texture>();
	m_ContainerTex->loadTexture("assets/textures/container2.png");

	m_ContainerSpecTex = std::make_shared<GLCore::Utils::Texture>();
	m_ContainerSpecTex->loadTexture("assets/textures/container2_specular.png");

	m_Shader[0]->use();
	m_Shader[0]->setInt("material.diffuse", 0);
	m_Shader[0]->setInt("material.specular", 1);

	
	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// positions          // normals           // texture coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,

		-0.3f, -0.3f, -0.3f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
		 0.3f, -0.3f, -0.3f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
		 0.3f, -0.3f,  0.3f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		 0.3f, -0.3f,  0.3f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		-0.3f, -0.3f,  0.3f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
		-0.3f, -0.3f, -0.3f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
	};


	glGenVertexArrays(1, &m_CubeVAO);
	glGenBuffers(1, &m_VBO);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	glBindVertexArray(m_CubeVAO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	
	glGenVertexArrays(1, &m_LightCubeVAO);
	glBindVertexArray(m_LightCubeVAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
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
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//LOG_INFO(m_Container01Tex->GetRendererID());

	
	float currentFrame = glfwGetTime();
	m_DeltaTime		   = currentFrame - m_LastFrame;
	m_LastFrame		   = currentFrame;
	m_Camera.m_MovementSpeed = m_SpeedFactor* m_DeltaTime;

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_ContainerTex->GetRendererID());
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_ContainerSpecTex->GetRendererID());

	// get matrix's uniform location and set matrix
	m_Shader[0]->use();
	m_Shader[0]->setFloat("material.shininess", m_Shininess);

	/*glm::vec3 lightColor;
	lightColor.x = sin(glfwGetTime() * 2.0f);
	lightColor.y = sin(glfwGetTime() * 0.7f);
	lightColor.z = sin(glfwGetTime() * 1.3f);

	glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
	glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f);*/

	m_Shader[0]->setVec3("light.position", m_LightPos);
	m_Shader[0]->setVec3("viewPos", m_Camera.m_Position);
	m_Shader[0]->setVec3("light.direction", m_Camera.m_Front);
	m_Shader[0]->setFloat("light.cutOff", glm::cos(glm::radians(m_Cutoff)));
	m_Shader[0]->setFloat("light.outerCutOff", glm::cos(glm::radians(17.5f)));

	m_Shader[0]->setVec3("light.ambient", 0.1f, 0.1f, 0.1f);
	m_Shader[0]->setVec3("light.diffuse", 0.8f, 0.8f, 0.8f);
	m_Shader[0]->setVec3("light.specular", 1.0f, 1.0f, 1.0f);

	m_Shader[0]->setFloat("light.constant", 1.0f);
	m_Shader[0]->setFloat("light.linear", 0.09f);
	m_Shader[0]->setFloat("light.quadratic", 0.032f);

	
	// create transformations
	glm::mat4 model      = glm::mat4(1.0f);
	glm::mat4 model1     = glm::mat4(1.0f);
	// model1               = glm::rotate(model1, float(glfwGetTime()), glm::vec3(1, 0.3, 0.2));
	glm::mat4 view       = m_Camera.GetViewMatrix();
	glm::mat4 projection = glm::perspective(glm::radians(m_Camera.m_Zoom), m_Width / m_Height, 0.1f, 100.0f);

	// pass them to the shaders
	m_Shader[0]->setMat4("model", model1);
	m_Shader[0]->setMat4("view", view);
	m_Shader[0]->setMat4("projection", projection);
	m_Shader[0]->setVec3("viewPos", m_Camera.m_Position);

	glBindVertexArray(m_CubeVAO);
	for (unsigned int i = 0; i < 10; i++)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, cubePositions[i]);
		float angle = 20.0f * i;
		model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
		m_Shader[0]->setMat4("model", model);

		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
	
	

	//// draw the lamp object
	//m_Shader[1]->use();
	//model = glm::mat4(1.0f);
	//model = glm::translate(model, m_LightPos);
	//model = glm::scale(model, glm::vec3(0.2f));
	//m_Shader[1]->setMat4("model", model);
	//m_Shader[1]->setMat4("view", view);
	//m_Shader[1]->setMat4("projection", projection);

	//m_Shader[1]->setVec3("lightColor", 1.0f, 1.0f, 1.0f);

	//glBindVertexArray(m_LightCubeVAO);
	//glDrawArrays(GL_TRIANGLES, 0, 36);
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
	ImGui::Text("m_Cutoff");
	ImGui::SliderFloat("m_Cutoff: ", &m_Cutoff, 0.0f, 512.0f);

	ImGui::Text(" ");
	ImGui::Text("lightPos: ");
	ImGui::SliderFloat("lightPos.x: ", &m_LightPos.x, -10.0f, 10.0f);
	ImGui::SliderFloat("lightPos.y: ", &m_LightPos.y, -10.0f, 10.0f);
	ImGui::SliderFloat("lightPos.z: ", &m_LightPos.z, -10.0f, 10.0f);




	ImGui::End();
}
