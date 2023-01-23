#include "../../include/opengl_utils/Windowing/Window.h"
#include "../../include/opengl_utils/Windowing/GLFW_Window.h"
#include "../../include/opengl_utils/Windowing/Win32_Window.h"

#include <glad/glad.h>




namespace GNF::OpenGL::Windowing
{
	OpenGL_Window::OpenGL_Window(const SU::Windowing::WindowProps& props, SU::Logging::ILogger* logger) : m_windowType(SU::Windowing::GLFW), m_props(props), m_logger(logger)
	{
	}

	bool OpenGL_Window::IsOpen()
	{
		return window->IsOpen();
	}
	void OpenGL_Window::Init(SU::Windowing::WindowType windowType)
	{
		if (windowType != SU::Windowing::GLFW && windowType != SU::Windowing::Win32)
			throw std::exception("OpenGL doesn't support this window type");

		m_windowType = windowType;
		switch (m_windowType)
		{
			case SU::Windowing::GLFW:
				m_logger->Info("Init GLFW Window Type");
				InitGLFW();
				break;
			case SU::Windowing::Win32:
				m_logger->Info("Init Win32 Window Type");
				InitWin32();
				break;
		}

	}
	const SU::Windowing::WindowProps* OpenGL_Window::GetProps()
	{
		return window->GetProps();
	}
	SU::Windowing::WindowType OpenGL_Window::GetWindowType()
	{
		return m_windowType;
	}
	std::any OpenGL_Window::GetNativeWindowHandler()
	{
		return window->GetNativeWindowHandler();
	}
	void OpenGL_Window::HandleEventsIfAny()
	{
		window->HandleEventsIfAny();
	}
	void OpenGL_Window::SwapBuffers()
	{
		window->SwapBuffers();
	}
	SU::Mouse::IMouse* OpenGL_Window::GetMouse()
	{
		return window->GetMouse();
	}
	SU::Keyboard::IKeyboard* OpenGL_Window::GetKeyboard()
	{
		return window->GetKeyboard();
	}
	void OpenGL_Window::ClearColor(float r, float g, float b, float a)
	{
		window->ClearColor(r, g, b, a);
	}
	void OpenGL_Window::ClearBufferBit(int bit)
	{
		window->ClearBufferBit(bit);
	}
	void OpenGL_Window::ClearBufferBit()
	{
		window->ClearBufferBit();
	}
	void OpenGL_Window::Close()
	{
		window->Close();
	}
	void OpenGL_Window::SetOnResizeCallBack(std::function<void(int newWidth, int newHeight, int prevWidth, int prevHeight)> func)
	{
		window->SetOnResizeCallBack(func);
	}

	void OpenGL_Window::SetOnMouseMoveCallBack(std::function<void(float posX, float posY)> func)
	{
		window->SetOnMouseMoveCallBack(func);
	}

	void OpenGL_Window::SetOnMouseClickCallBack(std::function<void(int button, int action, float posX, float posY)> func)
	{
		window->SetOnMouseClickCallBack(func);
	}

	void OpenGL_Window::SetOnKeyboardCallBack(std::function<void(int key, int scancode, int action)> func)
	{
		window->SetOnKeyboardCallBack(func);
	}

	void OpenGL_Window::InitGLFW()
	{
		window.reset(new GLFW_Window(m_props,m_logger));
		window->Init(m_windowType);
	}
	void OpenGL_Window::InitWin32()
	{
		window.reset(new Win32_Window(m_props, m_logger));
		window->Init(m_windowType);
	}
}