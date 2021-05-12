#include <Satoshi/stpch.hpp>
#include "GLFWindow.hpp"

#include <Satoshi/Events/ApplicationEvent.hpp>
#include <Satoshi/Events/KeyEvent.hpp>
#include <Satoshi/Events/MouseEvent.hpp>
#include <Satoshi/Core/MessageQueue.hpp>

#include <glad/gl.h>

static uint16_t s_GLFWindowCount = 0;

static void GLFWErrorCallback(int error, const char* description)
{
	ST_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
}

Satoshi::GLFWindow::GLFWindow(const WindowProps& props)
{
	Init(props);
}

Satoshi::GLFWindow::~GLFWindow()
{
	Shutdown();
}

void Satoshi::GLFWindow::Init(const WindowProps& props)
{

	m_Data.Title = props.Title;
	m_Data.Width = props.Width;
	m_Data.Height = props.Height;

	ST_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

	if (s_GLFWindowCount == 0)
	{
		int success = glfwInit();
		ST_CORE_ASSERT(success, "Could not initialize GLFW!");
		glfwSetErrorCallback(GLFWErrorCallback);
	}

	m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
	++s_GLFWindowCount;

	glfwMakeContextCurrent(m_Window);

	int status = gladLoadGL(glfwGetProcAddress);
	ST_CORE_ASSERT(status, "Failed to initialize GLAD");

	glfwSetWindowUserPointer(m_Window, &m_Data);
	SetVSync(true);

	SetGLCallbacks();
}

void Satoshi::GLFWindow::Shutdown()
{
	glfwDestroyWindow(m_Window);
	--s_GLFWindowCount;

	if (s_GLFWindowCount == 0)
	{
		glfwTerminate();
	}
}

void Satoshi::GLFWindow::SetGLCallbacks()
{
	glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
			MessageQueue::EnqueueMessage({ EventType::WindowResized, new WindowResizeData((unsigned)width, (unsigned)height) });
		});

	glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
		{
			MessageQueue::EnqueueMessage({ EventType::WindowClosed, nullptr });
		});

	glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			switch (action)
			{
			case GLFW_PRESS:
			{
				MessageQueue::EnqueueMessage({ EventType::KeyPressed, new KeyPressedData((unsigned)key, 0) });
				break;
			}
			case GLFW_RELEASE:
			{
				MessageQueue::EnqueueMessage({ EventType::KeyReleased, new KeyData((unsigned)key) });
				break;
			}
			case GLFW_REPEAT:
			{
				MessageQueue::EnqueueMessage({ EventType::KeyPressed, new KeyPressedData((unsigned)key, 1) });
				break;
			}
			}
		});

	glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
		{
			MessageQueue::EnqueueMessage({ EventType::CharTyped, new KeyData(keycode) });
		});

	glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
			case GLFW_PRESS:
			{
				MessageQueue::EnqueueMessage({ EventType::MouseButtonPressed, new MouseButtonData((unsigned)button) });
				break;
			}
			case GLFW_RELEASE:
			{
				MessageQueue::EnqueueMessage({ EventType::MouseButtonReleased, new MouseButtonData((unsigned)button) });
				break;
			}
			}
		});

	glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			MessageQueue::EnqueueMessage({ EventType::MouseScrolled, new MousePositionData((float)xOffset, (float)yOffset) });
		});

	glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
		{
			MessageQueue::EnqueueMessage({ EventType::MouseMoved, new MousePositionData((float)xPos, (float)yPos) });
		});
}

void Satoshi::GLFWindow::OnUpdate()
{

	glfwPollEvents();
	glfwSwapBuffers(m_Window);
}

void Satoshi::GLFWindow::SetVSync(bool enabled)
{
	if (enabled)
		glfwSwapInterval(1);
	else
		glfwSwapInterval(0);

	m_Data.VSync = enabled;
}

bool Satoshi::GLFWindow::IsVSync() const
{
	return m_Data.VSync;
}
