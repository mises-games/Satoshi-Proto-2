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
		static bool IsKeyPressed(uint16_t keycode) { return s_Instance->IsKeyPressedImpl(keycode); }
		static bool IsMouseButtonPressed(uint16_t button) { return s_Instance->IsMouseButtonPressedImpl(button); }
		static std::pair<float, float> GetMousePos() { return s_Instance->GetMousePosImpl(); }
		static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
		static float GetMouseY() { return s_Instance->GetMouseYImpl(); }
	protected:
		virtual bool IsKeyPressedImpl(uint16_t keycode) = 0;
		virtual bool IsMouseButtonPressedImpl(uint16_t button) = 0;
		virtual std::pair<float, float> GetMousePosImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;
	private:
		static Input* s_Instance;
	};
}

#endif
