#ifndef ENTRY_POINT_HPP
#define ENTRY_POINT_HPP

#include <Satoshi/stpch.hpp>
#include <Satoshi/Core/Application.hpp>
#include <Satoshi/Utils/StringSerializer.hpp>
#include <Satoshi/Utils/StringLocaler.hpp>
#include <Satoshi/FileSystem/FileHandler.hpp>
#include <cassert>

#include <yaml-cpp/yaml.h>

extern Satoshi::Application* Satoshi::CreateApplication();

int main(int argc, char** argv)
{
	Satoshi::RendererAPI api = Satoshi::RendererAPI::GL4;

	auto app = Satoshi::CreateApplication();
	app->Run();
	delete app;

	return 0;
}


#endif
