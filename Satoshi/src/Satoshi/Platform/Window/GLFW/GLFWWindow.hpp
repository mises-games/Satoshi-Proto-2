#ifndef GLFW_WINDOW_HPP
#define GLFW_WINDOW_HPP

#include <Satoshi/stpch.hpp>
#include <Satoshi/Core/Window.hpp>

#include <Satoshi/Renderer/GraphicsContext.hpp>
#include <GLFW/glfw3.h>

namespace Satoshi
{
	class GLFWWindow : public Window
	{
	public:
		GLFWWindow(const WindowProps& props);
		virtual ~GLFWWindow();

		virtual void OnUpdate() override;

		unsigned int GetWidth() const override { return m_Data.Width; }
		unsigned int GetHeight() const override { return m_Data.Height; }
		virtual void SetWidth(uint32_t width) override { m_Data.Width = width; }
		virtual void SetHeight(uint32_t height) override { m_Data.Height = height; }

		virtual double GetTime() const override { return glfwGetTime(); }

		virtual void SetVSync(bool enabled) override { m_Context->SetVSync(enabled); }
		virtual bool IsVSync() override { return m_Context->IsVSync(); }
		virtual void SetEventCallback(const EventCallbackFunction& callback) override { m_Data.EventCallback = callback; }

		virtual void Present() override { m_Context->Present(); }
		virtual void ClearBuffer() override { m_Context->ClearBuffer(); }

		virtual void* GetNativeWindow() override { return m_Window; }
		virtual GraphicsContext* GetContext() override { return m_Context; }

	private:
		void Init(const WindowProps& props);
		void Shutdown();

		void SetGLCallbacks();

		GLFWwindow* m_Window;
		GraphicsContext* m_Context;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;

			EventCallbackFunction EventCallback;
		};

		WindowData m_Data;
	};
}

#endif
