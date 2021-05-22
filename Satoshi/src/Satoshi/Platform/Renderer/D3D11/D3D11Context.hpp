#ifdef ST_PLATFORM_WINDOWS

#ifndef D3D11_CONTEXT_HPP
#define D3D11_CONTEXT_HPP

#include <Satoshi/stpch.hpp>
#include <Satoshi/Renderer/GraphicsContext.hpp>

#include <d3d11.h>
#include <backends/imgui_impl_dx11.h>

namespace Satoshi
{
	struct ImGuiDX11Init
	{
		ID3D11Device* Device;
		ID3D11DeviceContext* DeviceContext;

		ImGuiDX11Init(ID3D11Device* device, ID3D11DeviceContext* deviceContext) :
			Device(device), DeviceContext(deviceContext)
		{}
	};
	class D3D11Context : public GraphicsContext
	{
	public:
		D3D11Context(HWND windowHandle);

		virtual void Present() override;
		virtual void ClearBuffer() override;
		virtual void* GetNativeContextData() override;

		virtual void SetVSync(bool enabled) override { m_VSync = enabled; }

	private:
		void Init(HWND windowHandle);

		HWND m_WindowHandle;

		ID3D11Device* m_Device = nullptr;
		ID3D11DeviceContext* m_DeviceContext = nullptr;
		IDXGISwapChain* m_Swapper = nullptr;
		
		ID3D11RenderTargetView* m_TargetView;
		DXGI_SWAP_CHAIN_DESC swapDesc = {};

		bool m_VSync = false;
	};
}


#endif

#endif
