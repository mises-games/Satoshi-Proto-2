#include <Satoshi/stpch.hpp>
#include "GL4Context.hpp"


Satoshi::GL4Context::GL4Context(GLFWwindow* windowHandle) :
	m_WindowHandle(windowHandle)
{
}

void Satoshi::GL4Context::Init()
{
	glfwMakeContextCurrent(m_WindowHandle);
	int status = gladLoadGL(glfwGetProcAddress);
	ST_CORE_ASSERT(status, "Failed to initialize Glad!");
}

void Satoshi::GL4Context::SwapBuffers()
{
	glfwSwapBuffers(m_WindowHandle);
}