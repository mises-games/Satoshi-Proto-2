#ifndef GL4_CONTEXT_HPP
#define GL4_CONTEXT_HPP

#include <Satoshi/stpch.hpp>
#include <Satoshi/Renderer/GraphicsContext.hpp>

#include "gl_safe_include.h"
#include <backends/imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>

namespace Satoshi 
{
	struct GL4ContextData
	{
		std::string_view GLVersion;

		GL4ContextData(std::string_view glVersion) :
			GLVersion(glVersion)
		{}
	};

	class GL4Context : public GraphicsContext
	{
	public:

		GL4Context(GLFWwindow* windowHandle);
		virtual ~GL4Context();

		virtual void Present() override;
		virtual void ClearBuffer() override;
		virtual void* GetNativeContextData() override;

		virtual void SetVSync(bool enabled) override { m_VSync = enabled; }
		virtual bool IsVSync() override { return m_VSync; }

	private:
		GLFWwindow* m_WindowHandle;

		bool m_VSync = false;
	};
}

#endif // !GL4_CONTEXT
