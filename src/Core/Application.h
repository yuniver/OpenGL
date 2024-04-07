#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../Renderer/Shader.h"
#include "../Renderer/GraphicsContext.h"

namespace Terric
{
	class Application
	{
	public:
		//¥∞ø⁄…Ë÷√
		const float cameraSpeed = 0.05f;
		unsigned int SCR_WIDTH = 800;
		unsigned int SCR_HEIGHT = 600;


		void Prepare();
	public:
		int Init();

		virtual void OnRender(Shader* shader, unsigned int& VAO);
		virtual void OnDestroy();

		void Close();
	private:
		static Application* s_Instance;
		bool m_Running = true;
		GraphicsContext* m_Context;
	};
}
