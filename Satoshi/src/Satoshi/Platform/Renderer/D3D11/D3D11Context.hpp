#ifdef ST_PLATFORM_WINDOWS

#ifndef D3D11_CONTEXT_HPP
#define D3D11_CONTEXT_HPP

#include <Satoshi/stpch.hpp>
#include <Satoshi/Renderer/GraphicsContext.hpp>

#include <d3d11.h>
#include <Satoshi/Platform/Renderer/D3D11/D3D11ImGuiImpl.hpp>

namespace Satoshi
{
	class D3D11Context : public GraphicsContext
	{
	public:
		D3D11Context(HWND windowHandle);

		virtual void Present() override;
		virtual void ClearBuffer() override;

		virtual void ImGuiInit() override { ImGui_ImplDX11_Init(m_Device, m_DeviceContext); }
		virtual void ImGuiShutdown() override { ImGui_ImplDX11_Shutdown(); }
		virtual void ImGuiNewFrame() override { ImGui_ImplDX11_NewFrame(); }
		virtual void ImGuiRenderDrawData(ImDrawData* drawData) override { ImGui_ImplDX11_RenderDrawData(drawData); }

	private:
		void Init(HWND windowHandle);

		HWND m_WindowHandle;

		ID3D11Device* m_Device = nullptr;
		ID3D11DeviceContext* m_DeviceContext = nullptr;
		IDXGISwapChain* m_Swapper = nullptr;
		
		ID3D11RenderTargetView* m_TargetView;
		DXGI_SWAP_CHAIN_DESC swapDesc = {};
	};
}


#endif

#endif
