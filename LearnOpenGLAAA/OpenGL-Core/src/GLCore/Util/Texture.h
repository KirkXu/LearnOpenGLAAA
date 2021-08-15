#pragma once

#include <string>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include "GLCore/Core/Log.h"

namespace GLCore::Utils {

	class Texture {
	public:
		~Texture();
		void loadTexture(char const* path);

		GLuint GetRendererID() const  { return m_RendererID; }

	private:
		GLuint m_RendererID;
	};

}