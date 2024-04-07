#pragma once
#include "../../Renderer/Window.h"
#include "../../Renderer/GraphicsContext.h"

namespace Terric
{
	class OpenGLWindow : public Window
	{
	public:
		virtual ~OpenGLWindow() {};

		bool Init(const WindowProps& props) override;

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Width; }
		inline unsigned int GetHeight() const override { return m_Height; }

		virtual void ProcessInput() override;
		virtual bool IsRunning() override;
		virtual void ShutDown() override;
		virtual void* GetInstance() override;
	public:
		//virtual glm::mat4 GetViewProjectionMatrix() override;
	private:
		void ShowErrorMessage(GLenum errorCode);
	private:
		GLFWwindow* m_window;
		int m_Width, m_Height;
		GraphicsContext* m_Context;
		bool m_Running = true;		
		Camera camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));

		float deltaTime = 0.0f;	//每帧间隔时间
		float lastFrame = 0.0f;
	};
}