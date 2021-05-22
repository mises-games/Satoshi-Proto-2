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

		virtual void SetVSync(bool enabled) = 0;

		virtual void* GetNativeContextData() = 0;

		static GraphicsContext* Create(void * windowHandle);
	};
}

#endif
