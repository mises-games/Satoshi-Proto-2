#include <Satoshi/Core/Application.hpp>

int main() 
{
	Satoshi::Application *app = new Satoshi::Application();
	app->Run();
	delete app;

	return 0;
}