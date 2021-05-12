#include <Satoshi/Satoshi.hpp>

#if (defined(ST_PLATFORM_WINDOWS) && (defined(ST_RELEASE) || defined(ST_DIST)))

#include <SDKDDKVer.h>
#include <windows.h>

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	Satoshi::Application* app = new Satoshi::Application(Satoshi::RendererAPI::D3D11);
	app->Run();
	delete app;

	return 0;
}

#else

int main()
{
	Satoshi::Application* app = new Satoshi::Application(Satoshi::RendererAPI::D3D11);
	app->Run();
	delete app;

	return 0;
}

#endif