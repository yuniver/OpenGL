#include "OpenGLTexture.h"
#include <glad/glad.h>
#include <stb_image.h>
#include <iostream>

namespace Terric
{
	OpenGLTexture::~OpenGLTexture()
	{
		glDeleteTextures(1, &m_RendererID);
	}
	void OpenGLTexture::Bind(uint32_t slot) const
	{
		//glBindTextureUnit(slot, m_RendererID);
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, m_RendererID);
	}
	bool OpenGLTexture::Load(const std::string& path, bool isTransparent = false)
	{
		m_Path = path;

		glGenTextures(1, &m_RendererID);
		glBindTexture(GL_TEXTURE_2D, m_RendererID); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
		
		// set texture filtering parameters
		if (!isTransparent)
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
		else
		{
			// set the texture wrapping parameters
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}

		int width, height, nrChannels;
		stbi_set_flip_vertically_on_load(true);
		unsigned char* imgData = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
		if (imgData)
		{
			m_Width = width;
			m_Height = height;
			if (!isTransparent)
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, imgData);
			}
			else
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imgData);
			}

			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load texture:" << path << std::endl;
			stbi_image_free(imgData);
			return false;
		}
		stbi_image_free(imgData);

		return true;
	}

}
