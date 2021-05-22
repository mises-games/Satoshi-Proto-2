#include <Satoshi/stpch.hpp>
#include "GraphicsContext.hpp"

#include <Satoshi/Renderer/APIController.hpp>

#include <Satoshi/Platform/Renderer/GL4/GL4Context.hpp>
#include <Satoshi/Platform/Renderer/D3D11/D3D11Context.hpp>
#include <GLFW/glfw3.h>

Satoshi::GraphicsContext* Satoshi::GraphicsContext::Create(void* windowHandle)
{
	
	switch (APIController::GetRendererAPI())
	{
		case RendererAPI::None:	ST_CORE_ASSERT(false, "You must choose a valid Graphic API!"); return nullptr;
		case RendererAPI::GL4:	return new GL4Context((GLFWwindow *) windowHandle);
		#ifdef ST_PLATFORM_WINDOWS
		case RendererAPI::D3D11:	return new D3D11Context((HWND) windowHandle);
		#endif
	}
	
	return nullptr;
}
