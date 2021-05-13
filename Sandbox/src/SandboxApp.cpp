
#include <Satoshi/Satoshi.hpp>
#include <Satoshi/Core/EntryPoint.hpp>
#include <Satoshi/ImGui/ImGuiLayer.hpp>

class Sandbox : public Satoshi::Application
{
public:
	Sandbox() :
		Satoshi::Application(Satoshi::RendererAPI::D3D11)
	{
		PushLayer(new Satoshi::ImGuiLayer());
	}

	~Sandbox()
	{
	}
};

Satoshi::Application* Satoshi::CreateApplication()
{
	return new Sandbox();
}