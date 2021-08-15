#include "glpch.h"
#include "Texture.h"
#include "stb_image.h"
#include "glfw/glfw3.h"


namespace GLCore::Utils {

	void Texture::loadTexture(char const * path)
	{

		glGenTextures(1, &m_RendererID);

		glBindTexture(GL_TEXTURE_2D, m_RendererID); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object

		// set the texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		// load image, create texture and generate mipmaps
		int width, height, nrChannels;
		// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
		unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
		if (data)
		{
			GLenum tformat;
			if (nrChannels == 1)
				tformat = GL_RED;
			else if (nrChannels == 3)
				tformat = GL_RGB;
			else if (nrChannels == 4)
				tformat = GL_RGBA;
			glTexImage2D(GL_TEXTURE_2D, 0, tformat, width, height, 0, tformat, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
			LOG_INFO("Successd to load texture!");

		}
		else
		{
			LOG_INFO("Failed to load texture");
		}
		stbi_image_free(data);
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &m_RendererID);
	}
}