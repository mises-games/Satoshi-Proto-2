#include <Satoshi/stpch.hpp>
#include "Input.hpp"

#include <Satoshi/Renderer/APIController.hpp>

#include <Satoshi/Platform/Window/Win32/Win32Input.hpp>
#include <Satoshi/Platform/Window/GLFW/GLFWInput.hpp>

Satoshi::Input* Satoshi::Input::Create()
{
	switch (APIController::GetRendererAPI())
	{
	case RendererAPI::None:	ST_CORE_ASSERT(false, "You must choose a valid Graphic API!"); return nullptr;
	case RendererAPI::GL4:	return new GLFWInput();
	#ifdef ST_PLATFORM_WINDOWS
	case RendererAPI::D3D11: return new Win32Input();
	#endif
	default: ST_CORE_ASSERT(false, "Window not implemented in this OS"); return nullptr;
	}
}