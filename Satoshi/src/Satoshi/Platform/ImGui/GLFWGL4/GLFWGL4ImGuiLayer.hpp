#ifndef GLFW_GL4_IM_GUI_LAYER_HPP
#define GLFW_GL4_IM_GUI_LAYER_HPP

#ifdef ST_PLATFORM_WINDOWS

#include <Satoshi/stpch.hpp>
#include <Satoshi/ImGui/ImGuiLayer.hpp>
#include <GLFW/glfw3.h>

namespace Satoshi
{
	class GLFWGL4ImGuiLayer : public ImGuiLayer
	{
	public:
		GLFWGL4ImGuiLayer();
		~GLFWGL4ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		virtual void Begin() override;
		virtual void End() override;
	private:
		GLFWwindow* m_Window;
		std::string m_GLVersion;

		bool ShowContent = true;
	};
}

#endif

#endif
