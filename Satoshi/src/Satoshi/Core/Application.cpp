#include "Application.hpp"
#include "Log.hpp"
#include <iostream>

Satoshi::Application* Satoshi::Application::s_Instance = nullptr;

Satoshi::Application::Application()
{
	s_Instance = this;
	Satoshi::Log::Init();
}

Satoshi::Application::~Application()
{
}

void Satoshi::Application::Run()
{
	ST_CORE_INFO("test");
	ST_INFO("client test");
}
