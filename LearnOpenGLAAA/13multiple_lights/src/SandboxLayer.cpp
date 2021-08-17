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
		"assets/shaders/13.1.multiple_lights.vs.glsl",
		"assets/shaders/13.1.multiple_lights.fs.glsl"
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
	glClearColor(m_BackColor.x, m_BackColor.y, m_BackColor.z, 1.0f);
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

	// lights
	m_Shader[0]->setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
	m_Shader[0]->setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
	m_Shader[0]->setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
	m_Shader[0]->setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);

	m_Shader[0]->setVec3("pointLights[0].position", pointLightPositions[0]);
	m_Shader[0]->setVec3("pointLights[0].ambient", pointLightColor[0] * glm::vec3(0.05));
	m_Shader[0]->setVec3("pointLights[0].diffuse", pointLightColor[0] * glm::vec3(0.8));
	m_Shader[0]->setVec3("pointLights[0].specular", pointLightColor[0]);
	m_Shader[0]->setFloat("pointLights[0].constant", 1.0f);
	m_Shader[0]->setFloat("pointLights[0].linear", 0.09f);
	m_Shader[0]->setFloat("pointLights[0].quadratic", 0.032f);

	m_Shader[0]->setVec3("pointLights[1].position", pointLightPositions[1]);
	m_Shader[0]->setVec3("pointLights[1].ambient", pointLightColor[1] * glm::vec3(0.05));
	m_Shader[0]->setVec3("pointLights[1].diffuse", pointLightColor[1] * glm::vec3(0.8));
	m_Shader[0]->setVec3("pointLights[1].specular", pointLightColor[1]);
	m_Shader[0]->setFloat("pointLights[1].constant", 1.0f);
	m_Shader[0]->setFloat("pointLights[1].linear", 0.09f);
	m_Shader[0]->setFloat("pointLights[1].quadratic", 0.032f);

	m_Shader[0]->setVec3("pointLights[2].position", pointLightPositions[2]);
	m_Shader[0]->setVec3("pointLights[2].ambient", pointLightColor[2] * glm::vec3(0.05));
	m_Shader[0]->setVec3("pointLights[2].diffuse", pointLightColor[2] * glm::vec3(0.8));
	m_Shader[0]->setVec3("pointLights[2].specular", pointLightColor[2]);
	m_Shader[0]->setFloat("pointLights[2].constant", 1.0f);
	m_Shader[0]->setFloat("pointLights[2].linear", 0.09f);
	m_Shader[0]->setFloat("pointLights[2].quadratic", 0.032f);

	m_Shader[0]->setVec3("pointLights[3].position", pointLightPositions[3]);
	m_Shader[0]->setVec3("pointLights[3].ambient", pointLightColor[3] * glm::vec3(0.05));
	m_Shader[0]->setVec3("pointLights[3].diffuse", pointLightColor[3]*glm::vec3(0.8));
	m_Shader[0]->setVec3("pointLights[3].specular", pointLightColor[3]);
	m_Shader[0]->setFloat("pointLights[3].constant", 1.0f);
	m_Shader[0]->setFloat("pointLights[3].linear", 0.09f);
	m_Shader[0]->setFloat("pointLights[3].quadratic", 0.032f);

	m_Shader[0]->setVec3("spotLight.position", m_Camera.m_Position);
	m_Shader[0]->setVec3("spotLight.direction", m_Camera.m_Front);
	m_Shader[0]->setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
	m_Shader[0]->setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
	m_Shader[0]->setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
	m_Shader[0]->setFloat("spotLight.constant", 1.0f);
	m_Shader[0]->setFloat("spotLight.linear", 0.09f);
	m_Shader[0]->setFloat("spotLight.quadratic", 0.032f);
	m_Shader[0]->setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
	m_Shader[0]->setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));


	
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
	
	

	// draw the lamp object
	m_Shader[1]->use();
	
	m_Shader[1]->setMat4("view", view);
	m_Shader[1]->setMat4("projection", projection);
	


	glBindVertexArray(m_LightCubeVAO);
	for (unsigned int i = 0; i < 4; i++)
	{
		model = glm::mat4(1.0f);
		glm::mat4 rotate0 = glm::mat4(1.0f);
		float time = sin(glfwGetTime());
		float rand1 = sin(std::rand());
		float rand2 = sin(std::rand());
		float rand3 = sin(std::rand());
		pointLightColor[i] = rand1 * glm::vec3(rand1, rand2, rand3);
		pointLightPositions[i] = glm::vec3(glm::rotate(rotate0, glm::radians(time * 10.0f), glm::vec3(0, sin(time), cos(time))) * glm::vec4(pointLightPositions[i],1.0));
		model = glm::translate(model, glm::vec3(sin(glfwGetTime()))*pointLightPositions[i]);
		model = glm::scale(model, glm::vec3(0.2f));
		m_Shader[1]->setMat4("model", model);
		m_Shader[1]->setVec3("lightColor", pointLightColor[i]);

		glDrawArrays(GL_TRIANGLES, 0, 36);
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

	ImGui::Text(" ");
	ImGui::Text("Shininess");
	ImGui::SliderFloat("Shininess: ", &m_Shininess, 0.0f, 512.0f);
	ImGui::Text(" ");

	ImGui::ColorEdit3("Back Ground Color", (float*)&m_BackColor);
	ImGui::Text(" ");

	ImGui::Text("PointLight1");
	ImGui::ColorEdit3("PointLight1 Color", (float*)&pointLightColor[0]);
	ImGui::SliderFloat("PointLight1.x: %.1f", &pointLightPositions[0].x, -50.0f, 50.0f);
	ImGui::SliderFloat("PointLight1y: %.1f", &pointLightPositions[0].y, -50.0f, 50.0f);
	ImGui::SliderFloat("PointLight1z: %.1f", &pointLightPositions[0].z, -50.0f, 50.0f);
	ImGui::Text(" ");

	ImGui::Text("PointLight2");
	ImGui::ColorEdit3("PointLight2 Color", (float*)&pointLightColor[1]);
	ImGui::SliderFloat("PointLight2.x: %.1f", &pointLightPositions[1].x, -50.0f, 50.0f);
	ImGui::SliderFloat("PointLight2.y: %.1f", &pointLightPositions[1].y, -50.0f, 50.0f);
	ImGui::SliderFloat("PointLight2.z: %.1f", &pointLightPositions[1].z, -50.0f, 50.0f);
	ImGui::Text(" ");

	ImGui::Text("PointLight3");
	ImGui::ColorEdit3("PointLight3 Color", (float*)&pointLightColor[2]);
	ImGui::SliderFloat("PointLight3.x: %.1f", &pointLightPositions[2].x, -50.0f, 50.0f);
	ImGui::SliderFloat("PointLight3.y: %.1f", &pointLightPositions[2].y, -50.0f, 50.0f);
	ImGui::SliderFloat("PointLight3.z: %.1f", &pointLightPositions[2].z, -50.0f, 50.0f);
	ImGui::Text(" ");

	ImGui::Text("PointLight4");
	ImGui::ColorEdit3("PointLight4 Color", (float*)&pointLightColor[3]);
	ImGui::SliderFloat("PointLight4.x: %.1f", &pointLightPositions[3].x, -50.0f, 50.0f);
	ImGui::SliderFloat("PointLight4.y: %.1f", &pointLightPositions[3].y, -50.0f, 50.0f);
	ImGui::SliderFloat("PointLight4.z: %.1f", &pointLightPositions[3].z, -50.0f, 50.0f);
	ImGui::Text(" ");


	ImGui::End();
}
