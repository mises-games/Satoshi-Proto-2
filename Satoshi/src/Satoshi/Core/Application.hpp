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
		Application(RendererAPI startAPI);
		virtual ~Application();

		void Run();
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline static Application& GetInstance() { return *s_Instance; }
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