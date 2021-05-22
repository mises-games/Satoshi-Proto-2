#ifndef INPUT_HPP
#define INPUT_HPP

#include <Satoshi/stpch.hpp>

namespace Satoshi
{
	class Input
	{
#ifdef ST_PLATFORM_WINDOWS
		friend class Win32Input;
#endif
	public:
		virtual bool IsKeyPressed(uint16_t keycode) = 0;
		virtual bool IsMouseButtonPressed(uint16_t button) = 0;
		virtual std::pair<float, float> GetMousePos() = 0;
		virtual float GetMouseX() = 0;
		virtual float GetMouseY() = 0;

		static Input* Create();
	};
}

#endif
