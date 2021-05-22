#ifndef GL4_CONTEXT_HPP
#define GL4_CONTEXT_HPP

#include <Satoshi/stpch.hpp>
#include <Satoshi/Renderer/GraphicsContext.hpp>

#include <glad/wgl.h>
#include <backends/imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_EXPOSE_NATIVE_WGL
#include <GLFW/glfw3native.h>

namespace Satoshi 
{
	class GL4Context : public GraphicsContext
	{
	public:

		GL4Context(GLFWwindow* windowHandle);
		virtual ~GL4Context();

		virtual void Present() override;
		virtual void ClearBuffer() override;
		virtual void* GetNativeContextData() override;

		virtual void SetVSync(bool enabled) override { m_VSync = enabled; }

	private:
		GLFWwindow* m_WindowHandle;

		bool m_VSync = false;
	};
}

#endif // !GL4_CONTEXT
