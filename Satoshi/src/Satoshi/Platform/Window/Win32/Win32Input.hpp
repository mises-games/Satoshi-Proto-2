#ifndef WIN32_INPUT_HPP
#define WIN32_INPUT_HPP

#ifdef ST_PLATFORM_WINDOWS

#include <Satoshi/Core/Input.hpp>
#include "Win32InputMapper.hpp"

namespace Satoshi
{
	class Win32Input : public Input
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

#endif
