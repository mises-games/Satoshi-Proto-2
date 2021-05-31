#ifndef ENTRY_POINT_HPP
#define ENTRY_POINT_HPP

#include <Satoshi/stpch.hpp>
#include <Satoshi/Core/Application.hpp>
#include <Satoshi/Utils/StringLocaler.hpp>
#include <Satoshi/FileSystem/FileHandler.hpp>
#include <cassert>

#include <yaml-cpp/yaml.h>

extern Satoshi::Application* Satoshi::CreateApplication();

#if (defined(ST_PLATFORM_WINDOWS) && (defined(ST_RELEASE) || defined(ST_DIST)))

#include <SDKDDKVer.h>
#include <windows.h>

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	auto app = Satoshi::CreateApplication();
	app->Run();
	delete app;

	return 0;
}

#else

int main(int argc, char** argv)
{
	auto app = Satoshi::CreateApplication();
	app->Run();
	delete app;

	return 0;
}


#endif

#endif
