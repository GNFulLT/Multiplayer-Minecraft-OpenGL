#include "../../include/opengl_utils/Windowing/GLFW_Window.h"
#include <glad/glad.h>


namespace GNF::OpenGL::Windowing
{
	GLFW_Window::GLFW_Window(const SU::Windowing::WindowProps& props, SU::Logging::ILogger* logger) : m_nativeWindow(nullptr), m_windowType(SU::Windowing::GLFW), m_props(props), m_logger(logger)
	{
		m_mouse.reset(new Mouse::GLFW_Mouse(m_logger));
		m_keyboard.reset(new Keyboard::GLFW_Keyboard(m_logger));
	}
	bool GLFW_Window::IsOpen()
	{
		return !glfwWindowShouldClose(m_nativeWindow);
	}
	void GLFW_Window::Init(SU::Windowing::WindowType windowType)
	{
		if (windowType != SU::Windowing::GLFW)
			throw std::exception("OpenGL doesn't support this window type");

		m_windowType = windowType;

		//!: Init Graphic Funcs
		if (!glfwInit())
			throw std::exception("GLFW Init didn't work properly");
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef _DEBUG
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif
		GLFWwindow* window = glfwCreateWindow(m_props.m_width, m_props.m_height, m_props.m_windowName.c_str(), NULL, NULL);
		if (window == NULL)
		{
			glfwTerminate();
			throw std::exception("GLFW Create Window didn't work properly");
		}

		glfwMakeContextCurrent(window);
		glfwSetWindowUserPointer(window, this);
		gladLoadGL();
		m_nativeWindow = window;
		auto g_framebuffer_size_callback = [](GLFWwindow* w, int width, int height)
		{
			((GLFW_Window*)glfwGetWindowUserPointer(w))->framebuffer_size_callback(w, width, height);
		};
		auto g_mouse_moved_callback = [](GLFWwindow* w, double posX, double posY)
		{
			((GLFW_Window*)glfwGetWindowUserPointer(w))->mouse_moved_callback(w, posX, posY);
		};
		auto g_mouse_clicked_callback = [](GLFWwindow* w, int button, int action, int mods)
		{
			((GLFW_Window*)glfwGetWindowUserPointer(w))->mouse_clicked_callback(w, button, action, mods);
		};
		auto g_keyboard_callback = [](GLFWwindow* w, int key, int scancode, int action, int mods)
		{
			((GLFW_Window*)glfwGetWindowUserPointer(w))->keyboard_callback(w, key, scancode, action, mods);
		};
		glfwSetFramebufferSizeCallback(window, g_framebuffer_size_callback);
		glfwSetMouseButtonCallback(window, g_mouse_clicked_callback);
		glfwSetCursorPosCallback(window, g_mouse_moved_callback);
		glfwSetKeyCallback(window, g_keyboard_callback);

		glfwSwapInterval(1);

	}
	const SU::Windowing::WindowProps* GLFW_Window::GetProps()
	{
		return &(this->m_props);
	}
	SU::Windowing::WindowType GLFW_Window::GetWindowType()
	{
		return m_windowType;
	}
	std::any GLFW_Window::GetNativeWindowHandler()
	{
		return m_nativeWindow;
	}
	void GLFW_Window::HandleEventsIfAny()
	{
		glfwPollEvents();
	}
	void GLFW_Window::SwapBuffers()
	{
		glfwSwapBuffers(m_nativeWindow);
	}
	SU::Mouse::IMouse* GLFW_Window::GetMouse()
	{
		return m_mouse.get();
	}
	SU::Keyboard::IKeyboard* GLFW_Window::GetKeyboard()
	{
		return m_keyboard.get();
	}
	void GLFW_Window::ClearColor(float r, float g, float b, float a)
	{
		glClearColor(r, g, b, a);
	}
	void GLFW_Window::ClearBufferBit(int bit)
	{
		glClear(bit);
	}
	void GLFW_Window::ClearBufferBit()
	{
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	}
	void GLFW_Window::Close()
	{
		glfwDestroyWindow(m_nativeWindow);
	}
	void GLFW_Window::SetOnResizeCallBack(std::function<void(int newWidth, int newHeight, int prevWidth, int prevHeight)> func)
	{
		m_resizeFunc = func;
	}

	void GLFW_Window::SetOnMouseMoveCallBack(std::function<void(float posX, float posY)> func)
	{
		m_mouseMovedFunc = func;
	}

	void GLFW_Window::SetOnMouseClickCallBack(std::function<void(int button, int action, float posX, float posY)> func)
	{
		m_mouseClickedFunc = func;
	}

	void GLFW_Window::SetOnKeyboardCallBack(std::function<void(int key, int scancode, int action)> func)
	{
		m_keyboardFunc = func;
	}

	void GLFW_Window::framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		if (m_resizeFunc)
		{
			m_resizeFunc(width, height, m_props.m_width, m_props.m_height);
		}
		m_props.m_width = width;
		m_props.m_height = height;
	}

	void GLFW_Window::mouse_moved_callback(GLFWwindow* window, double posX, double posY)
	{
		m_mouse->SetMousePos(posX, posY);
		if (m_mouseMovedFunc)
		{
			m_mouseMovedFunc(posX, posY);
		}
	}

	void GLFW_Window::mouse_clicked_callback(GLFWwindow* window, int button, int action, int mods)
	{
		if (action == GLFW_PRESS)
		{
			m_mouse->MouseKeyPressed(button);
		}
		else
		{
			m_mouse->MouseKeyReleased(button);
		}
		if (m_mouseClickedFunc)
		{
			auto mouse = m_mouse->GetMousePos();
			m_mouseClickedFunc(button, action, mouse.x, mouse.y);
		}


	}

	void GLFW_Window::keyboard_callback(GLFWwindow* w, int key, int scancode, int action, int mods)
	{
		if (action == GLFW_PRESS)
		{
			m_keyboard->KeyPressed(key);
		}
		else
		{
			m_keyboard->KeyReleased(key);
		}
		if (m_keyboardFunc)
			m_keyboardFunc(key, scancode, action);
	}

	
}