#ifdef ST_PLATFORM_WINDOWS

#include <Satoshi/stpch.hpp>
#include "D3D11Context.hpp"

Satoshi::D3D11Context::D3D11Context(HWND windowHandle) :
	m_WindowHandle(windowHandle)

{
}

void Satoshi::D3D11Context::Init()
{
	swapDesc.BufferDesc.Width = 0;
	swapDesc.BufferDesc.Height = 0;
	swapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapDesc.BufferDesc.RefreshRate.Numerator = 0;
	swapDesc.BufferDesc.RefreshRate.Denominator = 0;
	swapDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapDesc.SampleDesc.Count = 1; //Anti aliasing
	swapDesc.SampleDesc.Quality = 0;
	swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapDesc.BufferCount = 1;
	swapDesc.OutputWindow = m_WindowHandle;
	swapDesc.Windowed = TRUE;
	swapDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapDesc.Flags = 0;

	D3D11CreateDeviceAndSwapChain
	(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&swapDesc,
		&m_Swapper,
		&m_Device,
		nullptr,
		&m_DeviceContext
	);
	ST_CORE_ASSERT( !((m_Swapper == nullptr)||(m_Device==nullptr)||(m_DeviceContext==nullptr)),
		"Failed to initialize Direct 3D 11!");

	ST_CORE_INFO("Direct 3D initialized");
}

void Satoshi::D3D11Context::SwapBuffers()
{
}

#endif
