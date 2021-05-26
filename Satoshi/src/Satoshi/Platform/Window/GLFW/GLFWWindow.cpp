#include <Satoshi/stpch.hpp>
#include "GLFWWindow.hpp"

#include <Satoshi/Events/ApplicationEvent.hpp>
#include <Satoshi/Events/MouseEvent.hpp>
#include <Satoshi/Events/KeyEvent.hpp>

static uint8_t s_GLFWWindowCount = 0;

static void GLFWErrorCallback(int error, const char* description)
{
	ST_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
}

Satoshi::GLFWWindow::GLFWWindow(const WindowProps& props)
{
	Init(props);
}

Satoshi::GLFWWindow::~GLFWWindow()
{
	Shutdown();
}

void Satoshi::GLFWWindow::OnUpdate()
{
	glfwPollEvents();
	Present();
}

void Satoshi::GLFWWindow::Init(const WindowProps& props)
{
	m_Data.Title = props.Title;
	m_Data.Width = props.Width;
	m_Data.Height = props.Height;

	ST_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

	if (s_GLFWWindowCount == 0)
	{
		int success = glfwInit();
		ST_CORE_ASSERT(success, "Could not initialize GLFW!");
		glfwSetErrorCallback(GLFWErrorCallback);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	}
	
	m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
	++s_GLFWWindowCount;

	m_Context = GraphicsContext::Create(m_Window);
	SetVSync(true);

	glfwSetWindowUserPointer(m_Window, &m_Data);

	SetGLCallbacks();
}

void Satoshi::GLFWWindow::Shutdown()
{
	glfwDestroyWindow(m_Window);
	delete m_Context;

	--s_GLFWWindowCount;

	if (s_GLFWWindowCount == 0)
	{
		glfwTerminate();
	}
}

void Satoshi::GLFWWindow::SetGLCallbacks()
{
	glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
	{
		WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
		WindowResizeEvent event((unsigned)(width), (unsigned)(height));
		data->EventCallback(event);
	});

	glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
	{
		WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
		WindowCloseEvent event;
		data->EventCallback(event);
	});

	glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
		switch (action)
		{
			case GLFW_PRESS:
			{
				KeyPressedEvent event((unsigned)key, 0);
				data->EventCallback(event);
				break;
			}
			case GLFW_RELEASE:
			{
				KeyReleasedEvent event((unsigned)key);
				data->EventCallback(event);
				break;
			}
			case GLFW_REPEAT:
			{
				KeyPressedEvent event((unsigned)key, 1);
				data->EventCallback(event);
				break;
			}
		}
	});

	glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
	{
		WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
		CharTypedEvent event((unsigned)keycode);
		data->EventCallback(event);
	});

	glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
	{
		WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
		switch (action)
		{
		case GLFW_PRESS:
		{
			MouseButtonPressedEvent event((unsigned)button);
			data->EventCallback(event);
			break;
		}
		case GLFW_RELEASE:
		{
			MouseButtonReleasedEvent event((unsigned)button);
			data->EventCallback(event);
			break;
		}
		}
	});

	glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
	{
		WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
		MouseScrolledEvent event((float) xOffset, (float) yOffset);
		data->EventCallback(event);
	});

	glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
	{
		WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
		MouseMovedEvent event((float)xPos, (float)yPos);
		data->EventCallback(event);
	});
}
