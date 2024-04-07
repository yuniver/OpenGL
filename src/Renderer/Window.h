#pragma once
#include "Base.h"
#include <string>
#include "Renderer.h"

namespace Terric
{
	struct WindowProps
	{
		std::string Title;
		uint32_t Width;
		uint32_t Height;

		WindowProps(const std::string& title = "Terric Test",
			uint32_t width = 800,
			uint32_t height = 600)
			: Title(title), Width(width), Height(height)
		{
		}
	};

	class Window
	{
	public:
		virtual ~Window() = default;
		
		virtual bool Init(const WindowProps& props) = 0;
		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void ProcessInput() = 0;
		virtual bool IsRunning() = 0;
		virtual void ShutDown() = 0;
		virtual void* GetInstance() = 0;
	};
}