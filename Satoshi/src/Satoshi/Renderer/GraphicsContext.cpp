#include <Satoshi/stpch.hpp>
#include "GraphicsContext.hpp"

#include <Satoshi/Renderer/APIController.hpp>

#include <Satoshi/Platform/Renderer/GL4/GL4Context.hpp>
#include <Satoshi/Platform/Renderer/D3D11/D3D11Context.hpp>

Satoshi::GraphicsContext* Satoshi::GraphicsContext::Create(void* windowHandle)
{
	#ifdef ST_PLATFORM_WINDOWS
		switch (APIController::GetRendererAPI())
		{
			case RendererAPI::None:	ST_CORE_ASSERT(false, "You must choose a valid Graphic API!"); return nullptr;
			case RendererAPI::GL4:	return new GL4Context((HWND) windowHandle);
			case RendererAPI::D3D11:	return new D3D11Context((HWND) windowHandle);
		}
	#endif // ST_PLATFORM_WINDOWS
	return nullptr;
}
