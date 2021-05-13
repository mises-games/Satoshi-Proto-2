#ifndef GL4_CONTEXT_HPP
#define GL4_CONTEXT_HPP

#include <Satoshi/stpch.hpp>
#include <Satoshi/Renderer/GraphicsContext.hpp>

#include <glad/wgl.h>
#include <Satoshi/Platform/Renderer/GL4/GL4ImGuiImpl.hpp>

namespace Satoshi 
{
	class GL4Context : public GraphicsContext
	{
	public:
#ifdef ST_PLATFORM_WINDOWS
		GL4Context(HWND windowHandle);
		virtual ~GL4Context();
		
#else
#endif

		virtual void Present() override;
		virtual void ClearBuffer() override;

		virtual void ImGuiInit() override { ImGui_ImplOpenGL3_Init("#version 410"); }
		virtual void ImGuiShutdown() override { ImGui_ImplOpenGL3_Shutdown(); }
		virtual void ImGuiNewFrame() override { ImGui_ImplOpenGL3_NewFrame(); }
		virtual void ImGuiRenderDrawData(ImDrawData* drawData) override { ImGui_ImplOpenGL3_RenderDrawData(drawData); }

	private:
#ifdef ST_PLATFORM_WINDOWS
		HWND m_Win32WindowHandle;
		HDC m_HandleDevice;
		HGLRC m_GLContext;
#endif
	};
}

#endif // !GL4_CONTEXT
