#include <Satoshi/stpch.hpp>

#include "Window.hpp"

#include <Satoshi/Renderer/APIController.hpp>

#include <Satoshi/Platform/Window/Win32/Win32Window.hpp>
#include <Satoshi/Platform/Window/GLFW/GLFWWindow.hpp>

Satoshi::Window* Satoshi::Window::Create(const WindowProps& props)
{
	switch (APIController::GetRendererAPI())
	{
		case RendererAPI::None:	ST_CORE_ASSERT(false, "You must choose a valid Graphic API!"); return nullptr;
		case RendererAPI::GL4:	return new GLFWWindow(props);
		#ifdef ST_PLATFORM_WINDOWS
		case RendererAPI::D3D11: return new Win32Window(props);
		#endif
		default: ST_CORE_ASSERT(false, "Window not implemented in this OS"); return nullptr;
	}
}
