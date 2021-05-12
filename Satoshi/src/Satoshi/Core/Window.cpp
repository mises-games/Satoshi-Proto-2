#include <Satoshi/stpch.hpp>

#include "Window.hpp"

#include <Satoshi/Renderer/APIController.hpp>

#include <Satoshi/Platform/Window/GLFW/GLFWindow.hpp>
#include <Satoshi/Platform/Window/Win32/Win32Window.hpp>

Satoshi::Window* Satoshi::Window::Create(const WindowProps& props)
{
	switch (APIController::GetAPI())
	{
	case RendererAPI::None: ST_CORE_ERROR("You must set an Window API"); return nullptr;
	case RendererAPI::GL4: return new GLFWindow(props);
	case RendererAPI::D3D11: return new Win32Window(props);
	default: ST_CORE_ERROR("Unrecognized Window API"); return nullptr;
	}

}