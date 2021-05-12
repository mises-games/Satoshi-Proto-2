#ifndef WIN_32_WINDOW_HPP
#define WIN_32_WINDOW_HPP

#include <Satoshi/stpch.hpp>
#include <Satoshi/Core/Window.hpp>

namespace Satoshi
{
	class Win32Window : public Window
	{
	public:
		Win32Window(const WindowProps& props);
		virtual ~Win32Window();

		void OnUpdate() override;

		unsigned int GetWidth() const override { return m_Data.Width; }
		unsigned int GetHeight() const override { return m_Data.Height; }
		virtual void SetWidth(uint32_t width) override { m_Data.Width = width; }
		virtual void SetHeight(uint32_t height) override { m_Data.Height = height; }

		// Window attributes
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		virtual void* GetNativeWindow() const { return m_Window; }
	private:
		void Init(const WindowProps& props);
		void Shutdown();

		void SetStartupParameters(HINSTANCE* instance, LPWSTR* nCmdLine, uint16_t* nCmdShow);
		void SetWindowClass(WNDCLASSEXW* windowClass);
		void DefineWindowPosInitialization(LPPOINT initPoint, const RECT& windowRectangle);
		void CalculateWindowDimensionInitialization(LPRECT dimensions);

		static LRESULT Callback(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

		HWND m_Window;
		HINSTANCE m_HandleInstance;
		MSG m_MSG;

		struct WindowData
		{
			std::wstring Title;
			unsigned int Width, Height;
			bool VSync;
		};

		WindowData m_Data;
	};
}

#endif
