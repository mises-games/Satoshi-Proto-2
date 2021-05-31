#include <Satoshi/Satoshi.hpp>
#include "DemoLayer.hpp"

class Sandbox : public Satoshi::Application
{
public:
	Sandbox() :
		Satoshi::Application()
	{
		PushLayer(new DemoLayer());
	}

	~Sandbox()
	{
	}
};

Satoshi::Application* Satoshi::CreateApplication()
{
	return new Sandbox();
}