#include <Satoshi/stpch.hpp>
#include "Application.hpp"
#include "MessageQueue.hpp"

Satoshi::Application* Satoshi::Application::s_Instance = nullptr;

Satoshi::Application::Application(Satoshi::RendererAPI startAPI)
{
	s_Instance = this;
	Satoshi::Log::Init();

	APIController::SetAPI(startAPI);

	m_Window.reset(Window::Create());

	MessageQueue::Start(ST_BIND_EVENT_FUNCTION(Application::OnEvent));
}

Satoshi::Application::~Application()
{
	m_Window.reset();
	MessageQueue::End();
}

void Satoshi::Application::Run()
{
	while (m_Running)
		m_Window->OnUpdate();
}

void Satoshi::Application::OnEvent(Event& e)
{
	ST_CORE_TRACE(e.ToString());
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<WindowCloseEvent>(ST_BIND_EVENT_FUNCTION(Application::OnWindowClose));
	dispatcher.Dispatch<WindowResizeEvent>(ST_BIND_EVENT_FUNCTION(Application::OnWindowResize));

	for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
	{
		it--;
		(*it)->OnEvent(e);
		if (e.Handled)
			break;
	}
}

void Satoshi::Application::PushLayer(Layer* layer)
{
	m_LayerStack.PushLayer(layer);
}

void Satoshi::Application::PushOverlay(Layer* overlay)
{
	m_LayerStack.PushOverlay(overlay);
}

bool Satoshi::Application::OnWindowClose(WindowCloseEvent& e)
{
	m_Running = false;
	return true;
}

bool Satoshi::Application::OnWindowResize(WindowResizeEvent& e)
{
	m_Window->SetWidth(e.GetWidth());
	m_Window->SetHeight(e.GetHeight());
	return true;
}
