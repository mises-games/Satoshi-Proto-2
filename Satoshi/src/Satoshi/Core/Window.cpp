#include <Satoshi/stpch.hpp>

#include "Window.hpp"

#include <Satoshi/Renderer/APIController.hpp>

#include <Satoshi/Platform/Window/Win32/Win32Window.hpp>

Satoshi::Window* Satoshi::Window::Create(const WindowProps& props)
{
	#ifdef ST_PLATFORM_WINDOWS
		return new Win32Window(props);
	#else
		return nullptr;
	#endif
}