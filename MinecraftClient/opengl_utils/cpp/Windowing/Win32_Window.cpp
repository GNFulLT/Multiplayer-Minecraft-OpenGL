#include "../../include/opengl_utils/Windowing/Win32_Window.h"

#include "glad/glad.h"
#include <format>
#include <boost/locale.hpp>

#define GLAPI __declspec(dllexport)
#include <GL/gl.h>
#include <GL/GLU.h>


namespace GNF::OpenGL::Windowing
{

#define CheckAnyErrorOccurred(criticalMsg) { \
		auto err = GetLastError(); \
		if (err != 0) \
		{ \
			LPSTR messageBuffer = nullptr; \
			size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, \
				NULL, err, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL); \
			std::string message(messageBuffer, size); \
			LocalFree(messageBuffer); \
			m_logger->Critical(criticalMsg); \
			m_logger->Error(message);  \
			SetLastError(0); \
		}} \


	#define WGL_CONTEXT_MAJOR_VERSION_ARB     0x2091
	#define WGL_CONTEXT_MINOR_VERSION_ARB     0x2092
	#define WGL_CONTEXT_FLAGS_ARB             0x2094
	#define WGL_CONTEXT_CORE_PROFILE_BIT_ARB  0x00000001
	#define WGL_CONTEXT_PROFILE_MASK_ARB      0x9126
	typedef HGLRC(WINAPI* PFNWGLCREATECONTEXTATTRIBSARBPROC) (HDC, HGLRC, const int*);

	typedef const char* (WINAPI* PFNWGLGETEXTENSIONSSTRINGEXTPROC) (void);
	typedef BOOL(WINAPI* PFNWGLSWAPINTERVALEXTPROC) (int);
	typedef int (WINAPI* PFNWGLGETSWAPINTERVALEXTPROC) (void);

	Win32_Window::Win32_Window(const SU::Windowing::WindowProps& props, SU::Logging::ILogger* logger) : m_windowType(SU::Windowing::GLFW), m_props(props), m_logger(logger)
	{
		
	}

	bool Win32_Window::IsOpen()
	{
		return !m_wantedClose;
	}

	void Win32_Window::Init(SU::Windowing::WindowType windowType)
	{
		m_windowType = windowType;
		
		int size_needed = MultiByteToWideChar(CP_UTF8, 0, &m_props.m_windowName[0], (int)m_props.m_windowName.size(), NULL, 0);
		std::wstring wstrTo(size_needed, 0);
		MultiByteToWideChar(CP_UTF8, 0, &m_props.m_windowName[0], (int)m_props.m_windowName.size(), &wstrTo[0], size_needed);

		const wchar_t* className = wstrTo.c_str();

		auto hInstance = GetModuleHandle(NULL);
		
		//!: Class Name, hInstance and Window Proc Function setted
		WNDCLASSEX wndclass = { };
		wndclass.cbSize = sizeof(WNDCLASSEX);
		wndclass.style = CS_HREDRAW | CS_VREDRAW;
		wndclass.cbClsExtra = 0;
		wndclass.cbWndExtra = 0;
		wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
		wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
		wndclass.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
		wndclass.lpszClassName = className;
		wndclass.hInstance = hInstance;
		wndclass.lpfnWndProc = WndProc;

		//!: Say this is my unique class (window) to operating system
		RegisterClassEx(&wndclass);
		CheckAnyErrorOccurred("RegisterClassEx doesn't work");
		DWORD exStyle = 0;
		DWORD style = (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX);

		int x = m_props.m_posX;
		int y = m_props.m_posY;
		
		if(x <= 0)
			x = GetSystemMetrics(SM_CXSCREEN)/2;
		if (y <= 0)
			y = GetSystemMetrics(SM_CYSCREEN)/2;

		//!: Set Rect
		RECT windowRect;
		SetRect(&windowRect,
			(x) - (m_props.m_width / 2),
			(y) - (m_props.m_height / 2),
			(x) + (m_props.m_width / 2),
			(y) + (m_props.m_height / 2));
		//!: Set New Rect with Style
		AdjustWindowRectEx(&windowRect, style, FALSE, 0);

		m_hwnd = CreateWindowEx(exStyle, className, className,style,windowRect.left,windowRect.top,windowRect.right - windowRect.left,windowRect.bottom - windowRect.top,NULL,NULL, hInstance,this);
		SetWindowLongPtr(m_hwnd, GWLP_USERDATA, (LONG_PTR)this);

		if (m_hwnd == nullptr)
		{
			CheckAnyErrorOccurred("Cannot createwindowex");
		}

		InitOpenGL();

		//!: First Time to show window so SW_SHOWNORMAL
		ShowWindow(m_hwnd, SW_SHOWNORMAL);
		UpdateWindow(m_hwnd);

	}
	const SU::Windowing::WindowProps* Win32_Window::GetProps()
	{
		return &m_props;
	}
	SU::Windowing::WindowType Win32_Window::GetWindowType()
	{
		return m_windowType;
	}
	std::any Win32_Window::GetNativeWindowHandler()
	{
		return m_hwnd;
	}
	void Win32_Window::HandleEventsIfAny()
	{
		MSG msg;
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) {
				m_logger->Info("Win32 Closing Event Inside EventsIfany");
				this->Close();
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	void Win32_Window::SwapBuffers()
	{
		::SwapBuffers(m_hdc);
	}
	SU::Mouse::IMouse* Win32_Window::GetMouse()
	{
		return nullptr;
	}
	SU::Keyboard::IKeyboard* Win32_Window::GetKeyboard()
	{
		return nullptr;
	}
	void Win32_Window::ClearColor(float r, float g, float b, float a)
	{
		glClearColor(r, g, b, a);
	}
	void Win32_Window::ClearBufferBit(int bit)
	{
		glClear(GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}

	void Win32_Window::ClearBufferBit()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}

	void Win32_Window::Close()
	{
		m_wantedClose = true;
	}

	void Win32_Window::SetOnResizeCallBack(std::function<void(int newWidth, int newHeight, int prevWidth, int prevHeight)> func)
	{
		m_resizeFunc = func;
	}

	void Win32_Window::SetOnMouseMoveCallBack(std::function<void(float posX, float posY)> func)
	{
		m_mouseMovedFunc = func;
	}

	void Win32_Window::SetOnMouseClickCallBack(std::function<void(int button, int action, float posX, float posY)> func)
	{
		m_mouseClickedFunc = func;
	}

	void Win32_Window::SetOnKeyboardCallBack(std::function<void(int key, int scancode, int action)> func)
	{
		m_keyboardFunc = func;
	}

	

	void Win32_Window::InitOpenGL()
	{
		auto hdc = GetDC(m_hwnd);
		CheckAnyErrorOccurred("Error 1 ");
		m_hdc = hdc;
		PIXELFORMATDESCRIPTOR pfd;
		CheckAnyErrorOccurred("Error 24 ");
		//memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
		ZeroMemory(&pfd, sizeof(pfd));
		pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
		pfd.nVersion = 1;
		pfd.dwFlags = PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER;
		pfd.iPixelType = PFD_TYPE_RGBA;
		pfd.cColorBits = 24;
		pfd.cDepthBits = 32;
		pfd.cStencilBits = 8;
		pfd.iLayerType = PFD_MAIN_PLANE;
		auto hll = LoadLibrary(L"Gdi32.dll");
		typedef int (CALLBACK* LPFNDLLFUNC1)(HDC, PIXELFORMATDESCRIPTOR*);
		auto choosePixelFormat =(LPFNDLLFUNC1)GetProcAddress(hll,"ChoosePixelFormat");
		int pixelFormat = choosePixelFormat(hdc, &pfd);
		int pixelForr = ChoosePixelFormat(hdc, &pfd);
		FreeLibrary(hll);
		CheckAnyErrorOccurred("Error 23 ");
		SetPixelFormat(hdc, pixelFormat, &pfd);
		HGLRC tempRC = wglCreateContext(hdc);
		CheckAnyErrorOccurred("Error 22 ");
		wglMakeCurrent(hdc, tempRC);
		CheckAnyErrorOccurred("Error 2 ");

		PFNWGLCREATECONTEXTATTRIBSARBPROC
			wglCreateContextAttribsARB = NULL;
		wglCreateContextAttribsARB =
			(PFNWGLCREATECONTEXTATTRIBSARBPROC)
			wglGetProcAddress("wglCreateContextAttribsARB");
		CheckAnyErrorOccurred("Error 3 ");
		const int attribList[] = { WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
			WGL_CONTEXT_MINOR_VERSION_ARB, 6,
			WGL_CONTEXT_FLAGS_ARB, 0,
			WGL_CONTEXT_PROFILE_MASK_ARB,
			WGL_CONTEXT_CORE_PROFILE_BIT_ARB, 0, };

		HGLRC hglrc = wglCreateContextAttribsARB(hdc, 0, attribList);
		wglMakeCurrent(NULL, NULL);
		CheckAnyErrorOccurred("Error 4 ");
		wglDeleteContext(tempRC);
		wglMakeCurrent(hdc, hglrc);
		CheckAnyErrorOccurred("Error 5 ");
		if (!gladLoadGL()) {
			m_logger->Error("Couldn't load GLAD Win32");
			exit(-1);
		}
		else {
			m_logger->Info(std::format("OpenGL Version Major : {} Minor : {}", GLVersion.major, GLVersion.minor));
		}

		PFNWGLGETEXTENSIONSSTRINGEXTPROC
			_wglGetExtensionsStringEXT =
			(PFNWGLGETEXTENSIONSSTRINGEXTPROC)
			wglGetProcAddress("wglGetExtensionsStringEXT");
		bool swapControlSupported = strstr(
			_wglGetExtensionsStringEXT(),
			"WGL_EXT_swap_control") != 0;

		int vsynch = 0;
		if (swapControlSupported) {
			PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT =
				(PFNWGLSWAPINTERVALEXTPROC)
				wglGetProcAddress("wglSwapIntervalEXT");
			PFNWGLGETSWAPINTERVALEXTPROC
				wglGetSwapIntervalEXT =
				(PFNWGLGETSWAPINTERVALEXTPROC)
				wglGetProcAddress("wglGetSwapIntervalEXT");
			if (wglSwapIntervalEXT(0)) {
				m_logger->Info("Disabled vsynch");
				vsynch = wglGetSwapIntervalEXT();
				m_logger->Info(std::format("Vsync Key : {}", vsynch));
			}
			else {
				m_logger->Warn("Could not enable vsynch");
			}
		}
		else { // !swapControlSupported
			 m_logger->Warn("WGL_EXT_swap_control not supported");
		}
		CheckAnyErrorOccurred("Error ? ");
	}

	LRESULT CALLBACK Win32_Window::WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
	{
		Win32_Window* gApplication;
		gApplication = (Win32_Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);

		switch (iMsg)
		{
		case WM_CLOSE:
			gApplication->m_logger->Info("Win32 Window Wanted to Close");
			gApplication->Close();
			DestroyWindow(hwnd);
			break;
		case WM_DESTROY:
			gApplication->m_logger->Info("Win32 Window Wanted to Destroying");
			HDC hdc = GetDC(hwnd);
			HGLRC hglrc = wglGetCurrentContext();
			glBindVertexArray(0);
			wglMakeCurrent(NULL, NULL);
			wglDeleteContext(hglrc);
			ReleaseDC(hwnd, hdc);
			PostQuitMessage(0);
			break;
		}

		return DefWindowProc(hwnd, iMsg, wParam, lParam);

	}
}