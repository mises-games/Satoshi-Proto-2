#ifndef GLF_WINDOW_HPP
#define GLF_WINDOW_HPP

#include <Satoshi/Core/Window.hpp>
#include <GLFW/glfw3.h>

namespace Satoshi
{
	class GLFWindow : public Window
	{
	public:
		GLFWindow(const WindowProps& props);
		virtual ~GLFWindow();

		void OnUpdate() override;

		unsigned int GetWidth() const override { return m_Data.Width; }
		unsigned int GetHeight() const override { return m_Data.Height; }
		virtual void SetWidth(uint32_t width) override { m_Data.Width = width; }
		virtual void SetHeight(uint32_t height) override { m_Data.Height = height; }

		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		virtual void* GetNativeWindow() const { return m_Window; }
	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();

		void SetGLCallbacks();

		GLFWwindow* m_Window;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;
		};

		WindowData m_Data;
	};
}

#endif