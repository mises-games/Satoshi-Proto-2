#include <Satoshi/stpch.hpp>
#include "Win32Window.hpp"

#include <Satoshi/Events/ApplicationEvent.hpp>
#include <Satoshi/Events/KeyEvent.hpp>
#include <Satoshi/Events/MouseEvent.hpp>
#include <Satoshi/Core/MessageQueue.hpp>

static uint16_t s_Win32WindowCount = 0;

Satoshi::Win32Window::Win32Window(const WindowProps& props)
{
	Init(props);
}

Satoshi::Win32Window::~Win32Window()
{
	Shutdown();
}

void Satoshi::Win32Window::Init(const WindowProps& props)
{
	m_Data.Title = std::wstring(props.Title.begin(), props.Title.end());
	m_Data.Width = props.Width;
	m_Data.Height = props.Height;

	ST_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

	LPWSTR nCmdLine;
	uint16_t nCmdShow;
	WNDCLASSEXW windowClass = { 0 };
	POINT initPoint;
	RECT windowDimensions;

	SetStartupParameters(&m_HandleInstance, &nCmdLine, &nCmdShow);
	SetWindowClass(&windowClass);
	CalculateWindowDimensionInitialization(&windowDimensions);
	DefineWindowPosInitialization(&initPoint, windowDimensions);

	RegisterClassExW(&windowClass);

	m_Window = CreateWindowExW
	(
		0,
		m_Data.Title.c_str(),
		m_Data.Title.c_str(),
		WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_SYSMENU | WS_MINIMIZEBOX | WS_CAPTION | WS_MAXIMIZEBOX | WS_THICKFRAME,
		initPoint.x,
		initPoint.y,
		windowDimensions.right - windowDimensions.left,
		windowDimensions.bottom - windowDimensions.top,
		nullptr,
		nullptr,
		m_HandleInstance,
		nullptr
	);

	if (m_Window == nullptr)
	{
		ST_CORE_ASSERT(0, "Failed to open Win32 Window");
		return;
	}


	ShowWindow(m_Window, SW_SHOW);
	UpdateWindow(m_Window);

	SetVSync(true);
}

void Satoshi::Win32Window::Shutdown()
{
	DestroyWindow(m_Window);
	--s_Win32WindowCount;
}

void Satoshi::Win32Window::CalculateWindowDimensionInitialization(LPRECT dimensions)
{
	*dimensions = { 0, 0, (LONG)m_Data.Width, (LONG)m_Data.Height };
	AdjustWindowRectEx(dimensions, WS_OVERLAPPEDWINDOW, 0, 0);
}

LRESULT Satoshi::Win32Window::Callback(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
	{
		msg = WM_QUIT;
		MessageQueue::EnqueueMessage({ EventType::WindowClosed, nullptr });
		break;
	}
	case WM_QUIT:
	{
		MessageQueue::EnqueueMessage({ EventType::WindowClosed, nullptr });
		break;
	}
	case WM_SYSCOMMAND:
	{
		ST_CORE_TRACE("SC_RESTORE");
		ST_CORE_TRACE("SC_MINIMIZE");
		ST_CORE_TRACE("SC_MAXIMIZE");
		break;
	}
	case WM_SIZING:
	{
		RECT clientArea;
		GetClientRect(hwnd, &clientArea);
		MessageQueue::EnqueueMessage({ EventType::WindowResized, new WindowResizeData((unsigned)(clientArea.right - clientArea.left), (unsigned)(clientArea.bottom - clientArea.top)) });
		break;
	}

	case WM_MOUSEHWHEEL:
	{
		short delta = GET_WHEEL_DELTA_WPARAM(wParam);
		delta = delta / abs(delta);
		MessageQueue::EnqueueMessage({ EventType::MouseScrolled, new MousePositionData((float)delta, 0) });
		break;
	}
	case WM_MOUSEWHEEL:
	{
		short delta = GET_WHEEL_DELTA_WPARAM(wParam);
		delta = delta / abs(delta);
		MessageQueue::EnqueueMessage({ EventType::MouseScrolled, new MousePositionData(0, (float)delta) });
		break;
	}
	case WM_MOUSEMOVE:
	{
		RECT windowPos;
		POINT mousePos;
		GetWindowRect(hwnd, &windowPos);
		GetCursorPos(&mousePos);
		MessageQueue::EnqueueMessage({ EventType::MouseMoved, new MousePositionData((float)(mousePos.x - windowPos.left), (float)(mousePos.y - windowPos.top)) });
		break;
	}
	case WM_LBUTTONDOWN:
	{
		MessageQueue::EnqueueMessage({ EventType::MouseButtonPressed, new MouseButtonData(0) });
		break;
	}
	case WM_MBUTTONDOWN:
	{
		MessageQueue::EnqueueMessage({ EventType::MouseButtonPressed, new MouseButtonData(2) });
		break;
	}
	case WM_RBUTTONDOWN:
	{
		MessageQueue::EnqueueMessage({ EventType::MouseButtonPressed, new MouseButtonData(1) });
		break;
	}
	case WM_XBUTTONDOWN:
	{
		MessageQueue::EnqueueMessage({ EventType::MouseButtonPressed, new MouseButtonData((unsigned)wParam) });
		break;
	}
	case WM_LBUTTONUP:
	{
		MessageQueue::EnqueueMessage({ EventType::MouseButtonReleased, new MouseButtonData(0) });
		break;
	}
	case WM_MBUTTONUP:
	{
		MessageQueue::EnqueueMessage({ EventType::MouseButtonReleased, new MouseButtonData(2) });
		break;
	}
	case WM_RBUTTONUP:
	{
		MessageQueue::EnqueueMessage({ EventType::MouseButtonReleased, new MouseButtonData(1) });
		break;
	}
	case WM_XBUTTONUP:
	{
		MessageQueue::EnqueueMessage({ EventType::MouseButtonReleased, new MouseButtonData((unsigned)wParam) });
		break;
	}

	case WM_KEYDOWN:
	{
		uint16_t repeated = (bool)(HIWORD(lParam) & KF_REPEAT);
		MessageQueue::EnqueueMessage({ EventType::KeyPressed, new KeyPressedData((unsigned)wParam, repeated) });
		break;
	}
	case WM_KEYUP:
	{
		MessageQueue::EnqueueMessage({ EventType::KeyReleased, new KeyData((unsigned)wParam) });
		break;
	}
	case WM_CHAR:
	{
		MessageQueue::EnqueueMessage({ EventType::CharTyped, new KeyData((unsigned)wParam) });
		break;
	}
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

void Satoshi::Win32Window::SetStartupParameters(HINSTANCE* instance, LPWSTR* lpCmdLine, uint16_t* nCmdShow)
{
	*instance = GetModuleHandle(NULL);
	*lpCmdLine = GetCommandLineW();
	STARTUPINFO si;
	GetStartupInfo(&si);
	*nCmdShow = si.wShowWindow;
}

void Satoshi::Win32Window::SetWindowClass(WNDCLASSEXW* windowClass)
{
	windowClass->cbSize = sizeof(*windowClass);
	windowClass->style = CS_OWNDC;
	windowClass->lpfnWndProc = Win32Window::Callback;
	windowClass->cbClsExtra = 0;
	windowClass->cbWndExtra = 0;
	windowClass->hInstance = m_HandleInstance;
	windowClass->hIcon = nullptr;
	windowClass->hCursor = LoadCursor(m_HandleInstance, MAKEINTRESOURCE(230));
	windowClass->hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
	windowClass->lpszMenuName = nullptr;
	windowClass->lpszClassName = m_Data.Title.c_str();
}

void Satoshi::Win32Window::DefineWindowPosInitialization(LPPOINT initPoint, const RECT& windowRectangle)
{
	int width = GetSystemMetrics(SM_CXSCREEN);
	int height = GetSystemMetrics(SM_CYSCREEN);
	initPoint->x = (width - windowRectangle.right + windowRectangle.left) / 2;
	initPoint->y = (height - windowRectangle.bottom + windowRectangle.top) / 2;
}

void Satoshi::Win32Window::OnUpdate()
{
	MSG msg;
	GetMessage(&msg, m_Window, 0, 0);
	TranslateMessage(&msg);
	DispatchMessage(&msg);
}

void Satoshi::Win32Window::SetVSync(bool enabled)
{
	ST_CORE_WARN("Win32 needs D3D to set VSync");
	m_Data.VSync = enabled;
}

bool Satoshi::Win32Window::IsVSync() const
{
	return m_Data.VSync;
}
