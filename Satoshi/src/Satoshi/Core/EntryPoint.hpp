#ifndef ENTRY_POINT_HPP
#define ENTRY_POINT_HPP

#include <Satoshi/Core/Application.hpp>

extern Satoshi::Application* Satoshi::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Satoshi::CreateApplication();
	app->Run();
	delete app;

	return 0;
}


#endif
