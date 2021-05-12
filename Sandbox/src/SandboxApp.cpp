
#include <Satoshi/Satoshi.hpp>
#include <Satoshi/Core/EntryPoint.hpp>

class Sandbox : public Satoshi::Application
{
public:
	Sandbox() :
		Satoshi::Application(Satoshi::RendererAPI::D3D11)
	{
		
	}

	~Sandbox()
	{
	}
};

Satoshi::Application* Satoshi::CreateApplication()
{
	return new Sandbox();
}