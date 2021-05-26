#ifdef ST_PLATFORM_WINDOWS

#ifndef WIN_32_WINDOW_HPP
#define WIN_32_WINDOW_HPP

#include <Satoshi/stpch.hpp>
#include <Satoshi/Core/Window.hpp>

#include <Satoshi/Renderer/GraphicsContext.hpp>

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

		virtual double GetTime() const override 
		{
			uint64_t cycle;
			QueryPerformanceCounter((LARGE_INTEGER *) &cycle);
			return ((cycle - m_StartTime)*1.0/m_Frequency);
		}
		virtual void SetVSync(bool enabled) override { m_Context->SetVSync(enabled); }
		virtual bool IsVSync() override { return m_Context->IsVSync(); }
		virtual void SetEventCallback(const EventCallbackFunction& callback) override { m_Data.EventCallback = callback; }

		virtual void Present() override { m_Context->Present(); }
		virtual void ClearBuffer() override { m_Context->ClearBuffer(); }

		virtual void* GetNativeWindow() override { return m_Window; }
		virtual GraphicsContext* GetContext() override { return m_Context; }

		
	private:
		void Init(const WindowProps& props);
		void Shutdown();
		
		void SetStartupParameters(HINSTANCE* instance, LPWSTR* nCmdLine, uint16_t* nCmdShow);
		void SetWindowClass(WNDCLASSEXW* windowClass, HINSTANCE handleInstance, LPCWSTR className);
		void DefineWindowPosInitialization(LPPOINT initPoint, const RECT& windowRectangle);
		void CalculateWindowDimensionInitialization(LPRECT dimensions);
		
		static LRESULT Callback(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

		HWND m_Window;
		WNDCLASSEXW m_WindowClass = {0};
		GraphicsContext* m_Context;

		uint64_t val = 0;

		uint64_t m_StartTime;
		uint64_t m_Frequency;

		struct WindowData
		{
			std::wstring Title;
			unsigned int Width, Height;

			EventCallbackFunction EventCallback;
		};

		WindowData m_Data;
	};
}

#endif

#endif
