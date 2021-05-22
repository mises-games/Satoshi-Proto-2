#ifdef ST_PLATFORM_WINDOWS

#include <Satoshi/stpch.hpp>
#include "D3D11Context.hpp"

Satoshi::D3D11Context::D3D11Context(HWND windowHandle)
{
	Init(windowHandle);
}

void Satoshi::D3D11Context::Init(HWND windowHandle)
{
	HRESULT debug;
	swapDesc.BufferDesc.Width = 0;
	swapDesc.BufferDesc.Height = 0;
	swapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapDesc.SampleDesc.Count = 1; //Anti aliasing
	swapDesc.SampleDesc.Quality = 0;
	swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapDesc.BufferCount = 1;
	swapDesc.OutputWindow = windowHandle;
	swapDesc.Windowed = TRUE;
	swapDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapDesc.Flags = 0;

	debug = D3D11CreateDeviceAndSwapChain
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

	ST_CORE_ASSERT(debug == S_OK,"Failed to initialize Direct 3D 11!");

	ID3D11Resource* m_BackBuffer;
	debug = m_Swapper->GetBuffer(0, __uuidof(ID3D11Resource), reinterpret_cast<void **>(&m_BackBuffer));
	ST_CORE_ASSERT(debug == S_OK, "You must have a valid Direct3d Resource");
	debug = m_Device->CreateRenderTargetView(m_BackBuffer, nullptr, &m_TargetView);
	m_BackBuffer->Release();
	
	ST_CORE_INFO("Direct 3D initialized");
}

void Satoshi::D3D11Context::Present()
{
	HRESULT debug = m_Swapper->Present((UINT)m_VSync, 0);
}

void Satoshi::D3D11Context::ClearBuffer()
{
	const float Color[4] = { 0,.5f,.25f,1.0f };
	m_DeviceContext->OMSetRenderTargets(1, &m_TargetView, NULL);
	m_DeviceContext->ClearRenderTargetView(m_TargetView, Color);
}

void* Satoshi::D3D11Context::GetNativeContextData()
{
	return &ImGuiDX11Init(m_Device, m_DeviceContext);
}


#endif
