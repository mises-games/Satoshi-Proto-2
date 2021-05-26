#ifndef GLFW_INPUT_HPP
#define GLFW_INPUT_HPP

#include <Satoshi/Core/Input.hpp>
#include "GLFWInputMapper.hpp"

namespace Satoshi
{
	class GLFWInput : public Input
	{
	protected:
		virtual bool IsKeyPressedImpl(uint16_t keycode) override;
		virtual bool IsMouseButtonPressedImpl(uint16_t button) override;
		virtual std::pair<float, float> GetMousePosImpl() override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
	};
}

#endif
