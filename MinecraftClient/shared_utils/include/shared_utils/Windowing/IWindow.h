#pragma once

#include <glm/glm.hpp>
#include <string>
#include <any>
#include <functional>
#include "../Mouse/IMouse.h"
#include "../Keyboard/IKeyboard.h"
namespace GNF::SU::Windowing
{

	struct WindowProps
	{
		std::string m_windowName;
		float m_width;
		float m_height;
		float m_posX;
		float m_posY;

		WindowProps(){}
		WindowProps(const std::string& wname,float width,float height,float posX,float posY) : m_windowName(wname),m_width(width),m_height(height),m_posX(posX),
			m_posY(posY)
		{}
	};

	enum WindowType
	{GLFW = 0,Win32,UWP};

	class IWindow
	{

	public:
		virtual ~IWindow() = default;
		virtual bool IsOpen() = 0;
		virtual void Init(WindowType type) = 0;
		virtual const SU::Windowing::WindowProps* GetProps() = 0;
		virtual WindowType GetWindowType() = 0;
		virtual std::any GetNativeWindowHandler() = 0;
		virtual void HandleEventsIfAny() = 0;
		virtual void SwapBuffers() = 0;
		virtual Mouse::IMouse* GetMouse() = 0;
		virtual Keyboard::IKeyboard* GetKeyboard() = 0;
		virtual void ClearColor(float r, float g, float b, float a) = 0;
		virtual void ClearBufferBit(int bit)=0;
		virtual void ClearBufferBit() = 0;
		virtual void Close() = 0;
	public:
		//!: Abstract CallBacks
		virtual void SetOnResizeCallBack(std::function<void(int newWidth, int newHeight, int prevWidth, int prevHeight)> func) =0;
		virtual void SetOnMouseMoveCallBack(std::function<void(float posX, float posY)> func) = 0;
		virtual void SetOnMouseClickCallBack(std::function<void(int button,int action, float posX, float posY)> func) = 0;
		virtual void SetOnKeyboardCallBack(std::function<void(int key,int scancode,int action)> func) = 0;

	};
}
