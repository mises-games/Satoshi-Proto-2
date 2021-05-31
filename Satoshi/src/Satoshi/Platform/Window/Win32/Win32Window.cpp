#ifdef ST_PLATFORM_WINDOWS

#include <Satoshi/stpch.hpp>
#include "Win32Window.hpp"

#include <Satoshi/Events/ApplicationEvent.hpp>
#include <Satoshi/Events/KeyEvent.hpp>
#include <Satoshi/Events/MouseEvent.hpp>

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
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	Present();
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
	SetWindowClass(&m_WindowClass, handleInstance, m_Data.Title.c_str());
	CalculateWindowDimensionInitialization(&windowDimensions);
	DefineWindowPosInitialization(&initPoint, windowDimensions);

	RegisterClassExW(&m_WindowClass);

	m_Window = CreateWindowW
	(
		m_WindowClass.lpszClassName,
		m_Data.Title.c_str(),
		WS_OVERLAPPEDWINDOW,
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
		ST_CORE_CRITICAL("{0}", GetLastError());
		ST_CORE_ASSERT(0, "Failed to open Win32 Window {0}");
		return;
	}
	
	QueryPerformanceCounter((LARGE_INTEGER*)&m_StartTime);
	QueryPerformanceFrequency((LARGE_INTEGER*) &m_Frequency);

	m_Context = GraphicsContext::Create(m_Window);
	SetVSync(true);

	SetWindowLongPtrW(m_Window, 0, (LONG_PTR) &m_Data);

	ShowWindow(m_Window, SW_SHOW);
	UpdateWindow(m_Window);
}

void Satoshi::Win32Window::Shutdown()
{
	auto hInstance = m_WindowClass.hInstance;
	UnregisterClass(m_Data.Title.c_str(), m_WindowClass.hInstance);
	DestroyWindow(m_Window);
	FreeLibrary(hInstance);

	delete m_Context;
	
	--s_Win32WindowCount;
}

void Satoshi::Win32Window::CalculateWindowDimensionInitialization(LPRECT dimensions)
{
	*dimensions = { 0, 0, (LONG)m_Data.Width, (LONG)m_Data.Height };
	AdjustWindowRectEx(dimensions, WS_OVERLAPPEDWINDOW, 0, 0);
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT Satoshi::Win32Window::Callback(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	WindowData* data = (WindowData*)GetWindowLongPtr(hwnd, 0);

	if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wParam, lParam))
		return true;
	
	switch (msg)
	{
		case WM_CLOSE:
		case WM_QUIT:
		{
			WindowCloseEvent event;
			data->EventCallback(event);
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
			WindowResizeEvent event((unsigned)(clientArea.right - clientArea.left), (unsigned)(clientArea.bottom - clientArea.top));
			data->EventCallback(event);
			break;
		}

		case WM_MOUSEHWHEEL:
		{
			short delta = GET_WHEEL_DELTA_WPARAM(wParam);
			delta = delta / abs(delta);
			MouseScrolledEvent event((float)delta, 0);
			data->EventCallback(event);
			break;
		}
		case WM_MOUSEWHEEL:
		{
			short delta = GET_WHEEL_DELTA_WPARAM(wParam);
			delta = delta / abs(delta);
			MouseScrolledEvent event(0, (float)delta);
			data->EventCallback(event);
			break;
		}
		case WM_MOUSEMOVE:
		{
			RECT windowPos;
			POINT mousePos;
			GetWindowRect(hwnd, &windowPos);
			GetCursorPos(&mousePos);
			MouseMovedEvent event((float)(mousePos.x - windowPos.left), (float)(mousePos.y - windowPos.top));
			data->EventCallback(event);
			break;
		}
		case WM_LBUTTONDOWN:
		{
			MouseButtonPressedEvent event(0);
			data->EventCallback(event);
			break;
		}
		case WM_MBUTTONDOWN:
		{
			MouseButtonPressedEvent event(2);
			data->EventCallback(event);
			break;
		}
		case WM_RBUTTONDOWN:
		{
			MouseButtonPressedEvent event(1);
			data->EventCallback(event);
			break;
		}
		case WM_XBUTTONDOWN:
		{
			MouseButtonPressedEvent event((unsigned)wParam);
			data->EventCallback(event);
			break;
		}
		case WM_LBUTTONUP:
		{
			MouseButtonReleasedEvent event(0);
			data->EventCallback(event);
			break;
		}
		case WM_MBUTTONUP:
		{
			MouseButtonReleasedEvent event(2);
			data->EventCallback(event);
			break;
		}
		case WM_RBUTTONUP:
		{
			MouseButtonReleasedEvent event(1);
			data->EventCallback(event);
			break;
		}
		case WM_XBUTTONUP:
		{
			MouseButtonReleasedEvent event((unsigned)wParam);
			data->EventCallback(event);
			break;
		}

		case WM_KEYDOWN:
		{
			uint16_t repeated = (bool)(HIWORD(lParam) & KF_REPEAT);
			KeyPressedEvent event(static_cast<uint32_t>(wParam), repeated);
			data->EventCallback(event);
			break;
		}
		case WM_KEYUP:
		{
			KeyReleasedEvent event(static_cast<uint32_t>(wParam));
			data->EventCallback(event);
			break;
		}
		case WM_CHAR:
		{
			CharTypedEvent event(static_cast<uint32_t>(wParam));
			data->EventCallback(event);
			break;
		}
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

void Satoshi::Win32Window::SetStartupParameters(HINSTANCE* instance, LPWSTR* lpCmdLine, uint16_t* nCmdShow)
{
	if(*instance == nullptr)
		GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, NULL, instance);
	*lpCmdLine = GetCommandLineW();
	STARTUPINFO si;
	GetStartupInfo(&si);
	*nCmdShow = si.wShowWindow;
}

void Satoshi::Win32Window::SetWindowClass(WNDCLASSEXW* windowClass, HINSTANCE handleInstance, LPCWSTR className)
{
	windowClass->cbSize = sizeof(*windowClass);
	windowClass->style = CS_CLASSDC;
	windowClass->lpfnWndProc = Win32Window::Callback;
	windowClass->cbClsExtra = 0;
	windowClass->cbWndExtra = sizeof(void*);
	windowClass->hInstance = handleInstance;
	windowClass->hIcon = nullptr;
	windowClass->hCursor = LoadCursor(handleInstance, MAKEINTRESOURCE(230));
	windowClass->hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
	windowClass->lpszMenuName = nullptr;
	windowClass->lpszClassName = className;
}

void Satoshi::Win32Window::DefineWindowPosInitialization(LPPOINT initPoint, const RECT& windowRectangle)
{
	int width = GetSystemMetrics(SM_CXSCREEN);
	int height = GetSystemMetrics(SM_CYSCREEN);
	initPoint->x = (width - windowRectangle.right + windowRectangle.left) / 2;
	initPoint->y = (height - windowRectangle.bottom + windowRectangle.top) / 2;
}

#endif