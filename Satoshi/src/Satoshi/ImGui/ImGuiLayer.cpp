#include <Satoshi/stpch.hpp>
#include "ImGuiLayer.hpp"

#include "imgui.h"

#include <Satoshi/Core/Application.hpp>
#include <Satoshi/Renderer/APIController.hpp>

#include <Satoshi/Platform/ImGui/Win32D3D11/Win32D3D11ImGuiLayer.hpp>
#include <Satoshi/Platform/ImGui/GLFWGL4/GLFWGL4ImGuiLayer.hpp>

namespace Satoshi {

	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer")
	{
	}

	ImGuiLayer* ImGuiLayer::CreateImGuiLayer()
	{

		#ifdef ST_PLATFORM_WINDOWS
		switch (APIController::GetRendererAPI())
		{
			case RendererAPI::GL4: return new GLFWGL4ImGuiLayer();
			case RendererAPI::D3D11: return new Win32D3D11ImGuiLayer();
			case RendererAPI::None:
			default: {ST_CORE_ASSERT(false, "You must set a valid graphic API"); return nullptr;}
		}
		#else
		
		ST_CORE_ASSERT(false, "Satoshi doesn't have support to this platform")
		return nullptr;
		
		#endif // ST_PLATFORM_WINDOWS

		
	}
	
}