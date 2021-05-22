#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <Satoshi/stpch.hpp>

#include <Satoshi/Events/Event.hpp>
#include <Satoshi/Renderer/GraphicsContext.hpp>
#include "Macros.hpp"
#include "Input.hpp"

namespace Satoshi {

	struct WindowProps
	{
		std::string Title;
		uint32_t Width;
		uint32_t Height;

		WindowProps(const std::string& title = "Satoshi Engine",
			uint32_t width = 1600,
			uint32_t height = 900)
			: Title(title), Width(width), Height(height)
		{
		}
	};

	// Interface representing a desktop system based Window
	class Window
	{
	public:

		virtual ~Window() = default;

		virtual void OnUpdate() = 0;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;
		virtual void SetWidth(uint32_t width) = 0;
		virtual void SetHeight(uint32_t height) = 0;

		virtual double GetTime() const = 0;

		virtual void SetVSync(bool enabled) = 0;

		virtual void Present() = 0;
		virtual void ClearBuffer() = 0;

		virtual void* GetNativeWindow() = 0;
		virtual GraphicsContext* GetContext() = 0;
		virtual Input* GetInput() = 0;

		static Window* Create(const WindowProps& props = WindowProps());
	};

}

#endif
