#include <Satoshi/stpch.hpp>
#include "GL4Context.hpp"

Satoshi::GL4Context::GL4Context(GLFWwindow *windowHandle) :
	m_WindowHandle(windowHandle)
{
	glfwMakeContextCurrent(m_WindowHandle);
	bool status_gl = gladLoadGL(glfwGetProcAddress);
	ST_CORE_ASSERT(status_gl, "Failed to initialize Glad!");
}

Satoshi::GL4Context::~GL4Context()
{
}

void Satoshi::GL4Context::Present()
{
	glfwSwapInterval((int)m_VSync);
	glfwSwapBuffers(m_WindowHandle);
}

void Satoshi::GL4Context::ClearBuffer()
{
	glClearColor(1, 1, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
}

void* Satoshi::GL4Context::GetNativeContextData()
{
	auto version = "#version 410";
	return &version;
}
