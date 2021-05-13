#include <Satoshi/stpch.hpp>
#include "GL4Context.hpp"

#ifdef ST_PLATFORM_WINDOWS
Satoshi::GL4Context::GL4Context(HWND windowHandle) :
	m_Win32WindowHandle(windowHandle)
{

	m_HandleDevice = GetDC(m_Win32WindowHandle);
	m_GLContext = wglCreateContext(m_HandleDevice);
	auto a = GetLastError();
	bool status = wglMakeCurrent(m_HandleDevice, m_GLContext);
	ST_CORE_ASSERT(status, "Failed to initialize OpenGL Win32!");
	status = gladLoaderLoadWGL(m_HandleDevice);
	gladLoaderLoadGL();
	ST_CORE_ASSERT(status, "Failed to initialize Glad!");
}

Satoshi::GL4Context::~GL4Context()
{
	wglDeleteContext(m_GLContext);
	DeleteDC(m_HandleDevice);
}


#endif

void Satoshi::GL4Context::Present()
{
#ifdef ST_PLATFORM_WINDOWS
	wglMakeCurrent(m_HandleDevice, m_GLContext);
	SwapBuffers(m_HandleDevice);
#endif
}

void Satoshi::GL4Context::ClearBuffer()
{
	glClearColor(1, 1, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
}
