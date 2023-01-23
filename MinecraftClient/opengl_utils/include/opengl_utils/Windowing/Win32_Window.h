#pragma once

#ifdef OPENGL_UTILS_EXPORTS
#define OPENGL_UTILS_API __declspec(dllexport)
#else
#define OPENGL_UTILS_API __declspec(dllimport)
#endif

#include <shared_utils/Windowing/IWindow.h>
#include <shared_utils/Logging/ILogger.h>

#include <windows.h>

namespace GNF::OpenGL::Windowing
{
	class OPENGL_UTILS_API Win32_Window : public SU::Windowing::IWindow
	{
	public:
		Win32_Window(const SU::Windowing::WindowProps& props, SU::Logging::ILogger* logger);
		virtual bool IsOpen() override;
		virtual void Init(SU::Windowing::WindowType windowType = SU::Windowing::GLFW) override;
		virtual const SU::Windowing::WindowProps* GetProps() override;
		virtual SU::Windowing::WindowType GetWindowType() override;
		virtual std::any GetNativeWindowHandler() override;
		virtual void HandleEventsIfAny() override;
		virtual void SwapBuffers() override;
		virtual SU::Mouse::IMouse* GetMouse() override;
		virtual SU::Keyboard::IKeyboard* GetKeyboard() override;
		virtual void ClearColor(float r, float g, float b, float a) override;
		virtual void ClearBufferBit(int bit) override;
		virtual void ClearBufferBit() override;
		virtual void Close() override;

		virtual void SetOnResizeCallBack(std::function<void(int newWidth, int newHeight, int prevWidth, int prevHeight)> func) override;
		virtual void SetOnMouseMoveCallBack(std::function<void(float posX, float posY)> func) override;
		virtual void SetOnMouseClickCallBack(std::function<void(int button, int action, float posX, float posY)> func) override;
		virtual void SetOnKeyboardCallBack(std::function<void(int key, int scancode, int action)> func) override;

		static LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
		private:
			void InitOpenGL();
		//!: Native Callbacks
	private:
		


	private:
		SU::Logging::ILogger* m_logger;
		SU::Windowing::WindowProps m_props;
		SU::Windowing::WindowType m_windowType;
		bool m_wantedClose = false;
	private:
		//!: Native Things
		HWND m_hwnd;
		HDC m_hdc;
		//!: Callbacks
	private:
		std::function<void(int newWidth, int newHeight, int prevWidth, int prevHeight)> m_resizeFunc;
		std::function<void(int posX, int posY)> m_mouseMovedFunc;
		std::function<void(int button, int action, int posX, int posY)> m_mouseClickedFunc;
		std::function<void(int key, int scancode, int action)> m_keyboardFunc;
	};
}