#ifndef GRAPHICS_CONTEXT_HPP
#define GRAPHICS_CONTEXT_HPP

#include <imgui.h>

namespace Satoshi
{
	class GraphicsContext 
	{
	public:
		virtual void Present() = 0;
		virtual void ClearBuffer() = 0;

		virtual void ImGuiInit() = 0;
		virtual void ImGuiShutdown() = 0;
		virtual void ImGuiNewFrame() = 0;
		virtual void ImGuiRenderDrawData(ImDrawData* drawData) = 0;

		static GraphicsContext* Create(void * windowHandle);
	};
}

#endif
