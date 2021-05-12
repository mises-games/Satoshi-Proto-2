#ifndef GL4_CONTEXT_HPP
#define GL4_CONTEXT_HPP

#include <Satoshi/stpch.hpp>
#include <Satoshi/Renderer/GraphicsContext.hpp>

#include <glfw/glfw3.h>
#include <glad/gl.h>

namespace Satoshi 
{
	class GL4Context : public GraphicsContext
	{
	public:
		GL4Context(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;

	private:
		GLFWwindow* m_WindowHandle;
	};
}

#endif // !GL4_CONTEXT
