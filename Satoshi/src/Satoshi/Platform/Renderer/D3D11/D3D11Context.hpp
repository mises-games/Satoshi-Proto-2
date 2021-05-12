#ifdef ST_PLATFORM_WINDOWS

#ifndef D3D11_CONTEXT_HPP
#define D3D11_CONTEXT_HPP

#include <Satoshi/stpch.hpp>
#include <Satoshi/Renderer/GraphicsContext.hpp>

#include <d3d11.h>

namespace Satoshi
{
	class D3D11Context : public GraphicsContext
	{
	public:
		D3D11Context(HWND windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;

	private:
		HWND m_WindowHandle;

		ID3D11Device* m_Device = nullptr;
		ID3D11DeviceContext* m_DeviceContext = nullptr;
		IDXGISwapChain* m_Swapper = nullptr;
		DXGI_SWAP_CHAIN_DESC swapDesc = {};
	};
}


#endif

#endif
