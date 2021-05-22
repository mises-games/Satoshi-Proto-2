#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <Satoshi/Renderer/APIController.hpp>
#include <Satoshi/Core/Window.hpp>
#include "MessageQueue.hpp"
#include <Satoshi/Events/ApplicationEvent.hpp>
#include <Satoshi/Core/LayerStack.hpp>
#include <Satoshi/ImGui/ImGuiLayer.hpp>

namespace Satoshi
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		float GetWindowTime() { return (float) m_Window->GetTime(); }
		Window* GetWindow() { return m_Window.get(); }

		uint32_t GetWindowWidth() const { return m_Window->GetWidth(); }
		uint32_t GetWindowHeight() const { return m_Window->GetHeight(); }

		inline static Application* GetInstance() { return s_Instance; }
	private:
		static Application* s_Instance;

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	};

	Application* CreateApplication();
}

#endif