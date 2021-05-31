#include <Satoshi/stpch.hpp>
#include "Application.hpp"
#include <Satoshi/FileSystem/FileHandler.hpp>
#include "Input.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <DirectXMath.h>
#include <Satoshi/Core/InputCodes.hpp>

Satoshi::Application* Satoshi::Application::s_Instance = nullptr;

Satoshi::Application::Application()
{
	std::string settings;
	bool read = Satoshi::FileHandler::Load("settings/settings.yaml", &settings);
	YAML::Node startupArgs = YAML::Load(settings);
	std::cout << "Loading Settings Files\n";
	assert(startupArgs["Window"]);

	s_Instance = this;
	Satoshi::Log::Init();

	APIController::SetRendererAPI((Satoshi::RendererAPI)startupArgs["Window"]["Renderer"].as<uint32_t>());

	m_Window.reset(Window::Create());

	m_ImGuiLayer = ImGuiLayer::CreateImGuiLayer();
	PushOverlay(m_ImGuiLayer);

	m_Sample = Satoshi::Sample::Create();
	m_Sample->Start(m_Window->GetContext()->GetNativeContextData());

	Input::Create();
	m_Window->SetEventCallback(ST_BIND_EVENT_FUNCTION(Application::OnEvent));
}

Satoshi::Application::~Application()
{
	m_Window.reset();
	Input::Destroy();
}

void Satoshi::Application::Run()
{
	
	while (m_Running) 
	{
		m_Window->ClearBuffer();

		for (Layer* layer : m_LayerStack)
			layer->OnUpdate();
		
		m_Sample->Update();

		m_ImGuiLayer->Begin();
		for (Layer* layer : m_LayerStack)
			layer->OnImGuiRender();
		m_ImGuiLayer->End();
		

		m_Window->OnUpdate();

		if(Input::IsKeyPressed(ST_KEY_A))
		{
			ST_CORE_INFO("A is pressed");
		}
	}
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
