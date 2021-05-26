#include <Satoshi/stpch.hpp>
#include "GLFWInput.hpp"
#include <Satoshi/Core/Application.hpp>
#include <GLFW/glfw3.h>

bool Satoshi::GLFWInput::IsKeyPressedImpl(uint16_t keycode)
{
	auto window = static_cast<GLFWwindow *>(Application::GetInstance()->GetWindow()->GetNativeWindow());
	auto state = glfwGetKey(window, Satoshi::GLFWInputMapper::MapInput(keycode));
	return (state == GLFW_PRESS || state == GLFW_REPEAT);
}

bool Satoshi::GLFWInput::IsMouseButtonPressedImpl(uint16_t button)
{
	auto window = static_cast<GLFWwindow*>(Application::GetInstance()->GetWindow()->GetNativeWindow());
	auto state = glfwGetMouseButton(window, Satoshi::GLFWInputMapper::MapInput(button));
	return (state == GLFW_PRESS || state == GLFW_REPEAT);
}

std::pair<float, float> Satoshi::GLFWInput::GetMousePosImpl()
{
	auto window = static_cast<GLFWwindow*>(Application::GetInstance()->GetWindow()->GetNativeWindow());
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	return std::pair<float, float>((float)xpos, (float)ypos);
}

float Satoshi::GLFWInput::GetMouseXImpl()
{
	return GetMousePosImpl().first;
}

float Satoshi::GLFWInput::GetMouseYImpl()
{
	return GetMousePosImpl().second;
}
