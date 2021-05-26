#include <Satoshi/stpch.hpp>
#include "GLFWGL4ImGuiLayer.hpp"

#ifdef ST_PLATFORM_WINDOWS

#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_glfw.h"
#include <Satoshi/Core/Application.hpp>
#include <Satoshi/Platform/Renderer/GL4/GL4Context.hpp>

Satoshi::GLFWGL4ImGuiLayer::GLFWGL4ImGuiLayer() :
	ImGuiLayer()
{
	auto app = Satoshi::Application::GetInstance();
	m_Window = static_cast<GLFWwindow*>(app->GetWindow()->GetNativeWindow());
	auto deviceHandler = static_cast<GL4ContextData*>(app->GetWindow()->GetContext()->GetNativeContextData());
	m_GLVersion = deviceHandler->GLVersion;
	delete deviceHandler;
}

Satoshi::GLFWGL4ImGuiLayer::~GLFWGL4ImGuiLayer()
{
}

void Satoshi::GLFWGL4ImGuiLayer::OnAttach()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();


	ImGuiIO& io = ImGui::GetIO();
	(void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

	ImGuiStyle& style = ImGui::GetStyle();
	ImGui::StyleColorsDark();

	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = .0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
	ImGui_ImplOpenGL3_Init(m_GLVersion.c_str());
}

void Satoshi::GLFWGL4ImGuiLayer::OnDetach()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void Satoshi::GLFWGL4ImGuiLayer::OnImGuiRender()
{
}

void Satoshi::GLFWGL4ImGuiLayer::Begin()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void Satoshi::GLFWGL4ImGuiLayer::End()
{
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	auto app = Application::GetInstance();
	io.DisplaySize = ImVec2((float)app->GetWindow()->GetWidth(), (float)app->GetWindow()->GetHeight());

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		GLFWwindow* backup_current_context = glfwGetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(backup_current_context);
	}
}

#endif