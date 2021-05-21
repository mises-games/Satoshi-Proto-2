#ifndef WIN32_INPUT_HPP
#define WIN32_INPUT_HPP

#ifdef ST_PLATFORM_WINDOWS

#include <Satoshi/Core/Input.hpp>

namespace Satoshi
{
	class Win32Input : public Input
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

#endif
