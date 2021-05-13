#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <Satoshi/Renderer/APIController.hpp>
#include <Satoshi/Core/Window.hpp>
#include "MessageQueue.hpp"
#include <Satoshi/Events/ApplicationEvent.hpp>
#include <Satoshi/Core/LayerStack.hpp>

namespace Satoshi
{
	class Application
	{
	public:
		Application(RendererAPI rendererAPI);
		virtual ~Application();

		void Run();
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		void WindowImGuiInit() { m_Window->ImGuiInit(); }
		void WindowImGuiShutdown() { m_Window->ImGuiShutdown(); }
		void WindowImGuiNewFrame() { m_Window->ImGuiNewFrame(); }

		void RendererImGuiInit() { m_Window->RendererImGuiInit(); }
		void RendererImGuiShutdown() { m_Window->RendererImGuiShutdown(); }
		void RendererImGuiNewFrame() { m_Window->RendererImGuiNewFrame(); }
		void RendererImGuiRenderDrawData(ImDrawData* drawData) { m_Window->RendererImGuiRenderDrawData(drawData); }

		float GetWindowTime() { return m_Window->GetTime(); }

		uint32_t GetWindowWidth() const { return m_Window->GetWidth(); }
		uint32_t GetWindowHeight() const { return m_Window->GetHeight(); }

		inline static Application* GetInstance() { return s_Instance; }
	private:
		static Application* s_Instance;

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;

		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	};

	Application* CreateApplication();
}

#endif