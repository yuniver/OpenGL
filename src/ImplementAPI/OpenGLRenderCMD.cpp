#include "OpenGLRenderCMD.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Terric
{
	void OpenGLRenderCMD::Init()
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	}

	void OpenGLRenderCMD::SetClearColor(const float red, const float green, const float blue, const float alpha)
	{
		glClearColor(red, green, blue, alpha);
	}

	void OpenGLRenderCMD::Draw(unsigned int VAO, unsigned int first, unsigned int count)
	{
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, first, count);
		glBindVertexArray(0);
	}

	void OpenGLRenderCMD::DrawScreen(unsigned int VAO, unsigned int first, unsigned int count)
	{
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLE_STRIP, first, count);
		glBindVertexArray(0);
	}

	void OpenGLRenderCMD::DrawIndexed(unsigned int VAO, unsigned int count)
	{
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

	void OpenGLRenderCMD::BindTexture(unsigned int index, unsigned int texturePtr)
	{
		glActiveTexture(GL_TEXTURE0 + index);
		glBindTexture(GL_TEXTURE_2D, texturePtr);
	}
	void OpenGLRenderCMD::BindFrameBuffer(unsigned int& FBO)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, FBO);
	}
	void OpenGLRenderCMD::UnbindFrameBuffer()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	void OpenGLRenderCMD::CreateFrameBuffer(unsigned int& FBO, unsigned int targetTexture)
	{
		glGenFramebuffers(1, &FBO);
		glBindFramebuffer(GL_FRAMEBUFFER, FBO);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, targetTexture, 0);
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	void OpenGLRenderCMD::SetView(int x, int y, int width, int height)
	{
		glViewport(x, y, width, height);
	}
	void OpenGLRenderCMD::Clear(int val)
	{
		glClear(val);
	}
}
