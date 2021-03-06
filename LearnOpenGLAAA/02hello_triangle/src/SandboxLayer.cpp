#include "SandboxLayer.h"

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

	int nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

	// Init here
	m_Shader.push_back(Shader::FromGLSLTextFiles(
		"assets/shaders/vs.vert.glsl",
		"assets/shaders/fs01.frag.glsl"
	));
	m_Shader.push_back(Shader::FromGLSLTextFiles(
		"assets/shaders/vs.vert.glsl",
		"assets/shaders/fs02.frag.glsl"
	));

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float triangle01[] = {
		-0.5f, 0.5f, 0.0f,
		 0.0f, 0.0f, 0.0f,
		 0.5f, 0.5f, 0.0f
	};
	float triangle02[] = {
		 0.0f,  0.0f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f
	};


	glGenVertexArrays(2, m_VAO);
	glGenBuffers(2, m_VBO);

	// triangle01 setup
	glBindVertexArray(m_VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle01), triangle01, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// triangle02 setup
	glBindVertexArray(m_VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle02), triangle02, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void SandboxLayer::OnDetach()
{
	// Shutdown here
	glDeleteVertexArrays(1, m_VAO);
	glDeleteBuffers(1, m_VBO);
	for (auto m : m_Shader)
	{
		glDeleteShader(m->GetRendererID());
	}
}

void SandboxLayer::OnEvent(Event& event)
{
	// Events here
}

void SandboxLayer::OnUpdate(Timestep ts)
{
	// Render here
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// draw triangle01
	glUseProgram(m_Shader[0]->GetRendererID());
	glBindVertexArray(m_VAO[0]); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
	glDrawArrays(GL_TRIANGLES, 0, 3);
	// draw triangle02
	glUseProgram(m_Shader[1]->GetRendererID());
	glBindVertexArray(m_VAO[1]);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glBindVertexArray(0);
}

void SandboxLayer::OnImGuiRender()
{
	// ImGui here
}
