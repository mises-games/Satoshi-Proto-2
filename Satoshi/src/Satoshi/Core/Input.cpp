#include <Satoshi/stpch.hpp>
#include "Input.hpp"

#include <Satoshi/Renderer/APIController.hpp>

#include <Satoshi/Platform/Window/Win32/Win32Input.hpp>
#include <Satoshi/Platform/Window/GLFW/GLFWInput.hpp>

Satoshi::Input* Satoshi::Input::s_Instance;

void Satoshi::Input::Create()
{
	switch (APIController::GetRendererAPI())
	{
	case RendererAPI::None:	ST_CORE_ASSERT(false, "You must choose a valid Graphic API!"); return;
	case RendererAPI::GL4:	s_Instance = new GLFWInput(); return;
	#ifdef ST_PLATFORM_WINDOWS
	case RendererAPI::D3D11: s_Instance = new Win32Input(); return;
	#endif
	default: ST_CORE_ASSERT(false, "Window not implemented in this OS"); return;
	}
}

void Satoshi::Input::Destroy()
{
	delete s_Instance;
}
