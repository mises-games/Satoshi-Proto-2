#include <Satoshi/stpch.hpp>
#include "Win32D3D11ImGuiLayer.hpp"

#ifdef ST_PLATFORM_WINDOWS

#include "backends/imgui_impl_dx11.h"
#include "backends/imgui_impl_win32.h"
#include <Satoshi/Core/Application.hpp>
#include <Satoshi/Platform/Renderer/D3D11/D3D11Context.hpp>

Satoshi::Win32D3D11ImGuiLayer::Win32D3D11ImGuiLayer() :
	ImGuiLayer()
{
	auto app = Satoshi::Application::GetInstance();
	m_Window = static_cast<HWND>(app->GetWindow()->GetNativeWindow());
	auto deviceHandler = static_cast<D3D11ContextData*>(app->GetWindow()->GetContext()->GetNativeContextData());
	m_Device = deviceHandler->Device;
	m_DeviceContext = deviceHandler->DeviceContext;
	delete deviceHandler;
}

Satoshi::Win32D3D11ImGuiLayer::~Win32D3D11ImGuiLayer()
{
}

void Satoshi::Win32D3D11ImGuiLayer::OnAttach()
{
	ImGui_ImplWin32_EnableDpiAwareness();

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	

	ImGuiIO& io = ImGui::GetIO();
	
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

	io.ConfigFlags |= ImGuiConfigFlags_DpiEnableScaleFonts;
	io.ConfigFlags |= ImGuiConfigFlags_DpiEnableScaleViewports;


	ImGuiStyle& style = ImGui::GetStyle();
	ImGui::StyleColorsDark();

	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = .0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	ImGui_ImplWin32_Init(m_Window);
	ImGui_ImplDX11_Init(m_Device, m_DeviceContext);
}

void Satoshi::Win32D3D11ImGuiLayer::OnDetach()
{
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

void Satoshi::Win32D3D11ImGuiLayer::OnImGuiRender()
{
}

void Satoshi::Win32D3D11ImGuiLayer::Begin()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void Satoshi::Win32D3D11ImGuiLayer::End()
{
	ImGuiIO& io = ImGui::GetIO();
	auto app = Application::GetInstance();
	io.DisplaySize = ImVec2((float) app->GetWindow()->GetWidth(), (float) app->GetWindow()->GetHeight());

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
	}

}

#endif
