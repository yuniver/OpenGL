#pragma once

namespace Terric
{
#define DEPTH_CLEAR 0x00000100
#define STENCIL_BUFFER_BIT 0x00000400
#define COLOR_CLEAR 0x00004000

	class OpenGLRenderCMD
	{
	public:
		static void Init();
		static void SetClearColor(const float red, const float green, const float blue, const float alpha);

		static void Draw(unsigned int VAO, unsigned int first, unsigned int count);
		static void DrawScreen(unsigned int VAO, unsigned int first, unsigned int count);
		static void DrawIndexed(unsigned int VAO, unsigned int count);
		static void BindTexture(unsigned int index, unsigned int texturePtr);
		static void BindFrameBuffer(unsigned int& FBO);
		static void UnbindFrameBuffer();
		static void CreateFrameBuffer(unsigned int& FBO, unsigned int targetTexture);
		static void SetView(int x, int y, int width, int height);
		static void Clear(int val);
		//static void DrawIndexed(const Ref<VertexArray>& vertexArray);
	};
}