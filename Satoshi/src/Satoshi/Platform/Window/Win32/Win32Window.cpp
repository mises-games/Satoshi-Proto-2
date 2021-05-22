#ifdef ST_PLATFORM_WINDOWS

#include <Satoshi/stpch.hpp>
#include "Win32Window.hpp"

#include <Satoshi/Events/ApplicationEvent.hpp>
#include <Satoshi/Events/KeyEvent.hpp>
#include <Satoshi/Events/MouseEvent.hpp>
#include <Satoshi/Core/MessageQueue.hpp>


#include <Satoshi/Renderer/GraphicsContext.hpp>

static uint16_t s_Win32WindowCount = 0;

Satoshi::Win32Window::Win32Window(const WindowProps& props)
{
	Init(props);
}

Satoshi::Win32Window::~Win32Window()
{
	Shutdown();
}

void Satoshi::Win32Window::OnUpdate()
{
	MSG msg;
	GetMessage(&msg, m_Window, 0, 0);
	TranslateMessage(&msg);
	DispatchMessage(&msg);
}

void Satoshi::Win32Window::Init(const WindowProps& props)
{
	m_Data.Title = std::wstring(props.Title.begin(), props.Title.end());
	m_Data.Width = props.Width;
	m_Data.Height = props.Height;

	ST_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

	LPWSTR nCmdLine;
	uint16_t nCmdShow;
	POINT initPoint;
	RECT windowDimensions;
	HINSTANCE handleInstance;

	SetStartupParameters(&handleInstance, &nCmdLine, &nCmdShow);
	SetWindowClass(&m_WindowClass, handleInstance);
	CalculateWindowDimensionInitialization(&windowDimensions);
	DefineWindowPosInitialization(&initPoint, windowDimensions);

	RegisterClassExW(&m_WindowClass);

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
		m_WindowClass.hInstance,
		nullptr
	);

	if (m_Window == nullptr)
	{
		ST_CORE_ASSERT(0, "Failed to open Win32 Window");
		return;
	}

	m_DeviceHandle = GetDC(m_Window);
	PIXELFORMATDESCRIPTOR pfd = GetPixelFormat();
	auto windowsPixelFormat = ChoosePixelFormat(m_DeviceHandle, &pfd);
	SetPixelFormat(m_DeviceHandle, windowsPixelFormat, &pfd);

	QueryPerformanceCounter((LARGE_INTEGER*)&m_StartTime);
	QueryPerformanceFrequency((LARGE_INTEGER*) &m_Frequency);

	m_Context = GraphicsContext::Create(m_Window);
	m_Input = Input::Create();
	SetVSync(true);

	ShowWindow(m_Window, SW_SHOW);
	UpdateWindow(m_Window);
}

void Satoshi::Win32Window::Shutdown()
{
	ReleaseDC(m_Window,m_DeviceHandle);
	DestroyWindow(m_Window);

	delete m_Context;
	delete m_Input;
	
	--s_Win32WindowCount;
}

void Satoshi::Win32Window::CalculateWindowDimensionInitialization(LPRECT dimensions)
{
	*dimensions = { 0, 0, (LONG)m_Data.Width, (LONG)m_Data.Height };
	AdjustWindowRectEx(dimensions, WS_OVERLAPPEDWINDOW, 0, 0);
}

PIXELFORMATDESCRIPTOR Satoshi::Win32Window::GetPixelFormat()
{
	PIXELFORMATDESCRIPTOR result = {};
	result.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	result.nVersion = 1;
	result.dwFlags = PFD_DRAW_TO_WINDOW | PFD_DIRECT3D_ACCELERATED | PFD_SUPPORT_OPENGL;
	result.iPixelType = PFD_TYPE_RGBA;
	result.cColorBits = 32;
	result.cDepthBits = 24;
	result.cStencilBits = 8;
	result.cAuxBuffers = 0;
	result.iLayerType = PFD_MAIN_PLANE;
	return result;
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT Satoshi::Win32Window::Callback(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wParam, lParam))
		return true;
	switch (msg)
	{
	case WM_ERASEBKGND:
		return 0;
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

void Satoshi::Win32Window::SetWindowClass(WNDCLASSEXW* windowClass, HINSTANCE handleInstance)
{
	windowClass->cbSize = sizeof(*windowClass);
	windowClass->style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	windowClass->lpfnWndProc = Win32Window::Callback;
	windowClass->cbClsExtra = 0;
	windowClass->cbWndExtra = 0;
	windowClass->hInstance = handleInstance;
	windowClass->hIcon = nullptr;
	windowClass->hCursor = LoadCursor(handleInstance, MAKEINTRESOURCE(230));
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

#endif