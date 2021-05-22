#ifndef GLFW_INPUT_HPP
#define GLFW_INPUT_HPP

#include <Satoshi/Core/Input.hpp>
#include "GLFWInputMapper.hpp"

namespace Satoshi
{
	class GLFWInput : public Input
	{
	public:
		virtual bool IsKeyPressed(uint16_t keycode) override;
		virtual bool IsMouseButtonPressed(uint16_t button) override;
		virtual std::pair<float, float> GetMousePos() override;
		virtual float GetMouseX() override;
		virtual float GetMouseY() override;
	};
}

#endif
