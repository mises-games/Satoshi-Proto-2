#ifdef ST_PLATFORM_WINDOWS

#ifndef WIN_32_WINDOW_HPP
#define WIN_32_WINDOW_HPP

#include <Satoshi/stpch.hpp>
#include <Satoshi/Core/Window.hpp>

#include <Satoshi/Platform/Renderer/D3D11/D3D11Context.hpp>
#include <Satoshi/Platform/Window/Win32/Win32ImGuiImpl.hpp>

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

		virtual void Present() override { m_Context->Present(); }
		virtual void ClearBuffer() override { m_Context->ClearBuffer(); }

		virtual void ImGuiInit() override { ImGui_ImplWin32_Init(m_Window); }
		virtual void ImGuiShutdown() override { ImGui_ImplWin32_Shutdown(); }
		virtual void ImGuiNewFrame() override { ImGui_ImplWin32_NewFrame(); }

		virtual void RendererImGuiInit() override { m_Context->ImGuiInit(); }
		virtual void RendererImGuiShutdown() override { m_Context->ImGuiShutdown(); }
		virtual void RendererImGuiNewFrame() override { m_Context->ImGuiNewFrame(); }
		virtual void RendererImGuiRenderDrawData(ImDrawData* drawData) override { m_Context->ImGuiRenderDrawData(drawData); }

	private:
		void Init(const WindowProps& props);
		void Shutdown();

		void SetStartupParameters(HINSTANCE* instance, LPWSTR* nCmdLine, uint16_t* nCmdShow);
		void SetWindowClass(WNDCLASSEXW* windowClass);
		void DefineWindowPosInitialization(LPPOINT initPoint, const RECT& windowRectangle);
		void CalculateWindowDimensionInitialization(LPRECT dimensions);
		PIXELFORMATDESCRIPTOR GetPixelFormat();

		static LRESULT Callback(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

		HWND m_Window;
		HINSTANCE m_HandleInstance;
		HDC m_DeviceHandle;
		GraphicsContext* m_Context;

		uint64_t m_StartTime;
		uint64_t m_Frequency;

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

#endif
