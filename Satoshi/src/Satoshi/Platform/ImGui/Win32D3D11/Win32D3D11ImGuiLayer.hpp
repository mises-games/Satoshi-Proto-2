#ifndef WIN32_D3D11_IM_GUI_LAYER_HPP
#define WIN32_D3D11_IM_GUI_LAYER_HPP

#ifdef ST_PLATFORM_WINDOWS

#include <Satoshi/stpch.hpp>
#include <Satoshi/ImGui/ImGuiLayer.hpp>
#include <d3d11.h>

namespace Satoshi
{
	class Win32D3D11ImGuiLayer : public ImGuiLayer
	{
	public:
		Win32D3D11ImGuiLayer();
		~Win32D3D11ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		virtual void Begin() override;
		virtual void End() override;
	private:
		bool m_ShowContent = true;
		HWND m_Window;
		ID3D11Device* m_Device;
		ID3D11DeviceContext* m_DeviceContext;
	};
}

#endif

#endif
