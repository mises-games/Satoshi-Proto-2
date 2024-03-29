#include <Satoshi/stpch.hpp>
#include "Win32Input.hpp"
#include <Satoshi/Core/Application.hpp>

#ifdef ST_PLATFORM_WINDOWS

bool Satoshi::Win32Input::IsKeyPressedImpl(uint16_t keycode)
{
	uint16_t keyState = GetKeyState(Satoshi::Win32InputMapper::MapInput((uint16_t) keycode));
	return keyState & BIT(15);
}

bool Satoshi::Win32Input::IsMouseButtonPressedImpl(uint16_t button)
{
	uint16_t buttonState = GetKeyState(Satoshi::Win32InputMapper::MapInput((uint16_t)button));
	return buttonState & BIT(15);
}

std::pair<float, float> Satoshi::Win32Input::GetMousePosImpl()
{
	HWND window = static_cast<HWND>(Satoshi::Application::GetInstance()->GetWindow()->GetNativeWindow());
	RECT windowPos;
	POINT mousePos;
	GetWindowRect(window, &windowPos);
	GetCursorPos(&mousePos);
	return std::pair<float, float>((float)(mousePos.x - windowPos.left), (float)(mousePos.y - windowPos.top));
}

float Satoshi::Win32Input::GetMouseXImpl()
{
	return GetMousePosImpl().first;
}

float Satoshi::Win32Input::GetMouseYImpl()
{
	return GetMousePosImpl().second;
}

#endif
