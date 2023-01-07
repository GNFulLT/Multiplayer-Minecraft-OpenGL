#pragma once

#include "ISystem.h"
#include <map>
#include <memory>
#include "glad_wrapper.h"
#include <GLFW/glfw3.h>
#include "Event/Event.h"

namespace GNF::Common
{
	struct MousePressedEventArgs
	{
		MousePressedEventArgs(int _key, int _action)
		{
			button = _key;
			action = _action;
		}
		int button;
		int action;
	};

	struct MouseMoveEventArgs
	{
		MouseMoveEventArgs(float x,float y,bool enabled):posx(x),posy(y),isCursorModeEnable(enabled)
		{}
		float posx;
		float posy;
		bool isCursorModeEnable;
	};

	struct KeyPressedEventArgs
	{
		KeyPressedEventArgs(int key, int act) : keyCode(key),action(act)
		{}
		int keyCode;
		int action;
	};

	class Window
	{
		public:


			Window(const Window&) = delete;
			
			static Window* CreateWindow();
			
			bool ShouldClose();

			void HandleEventsIfAny();

			template <class T>
			T* GetSystem()
			{
				return nullptr;
			}

			template <class T>
			Window* WithSystem(T*)
			{
				return nullptr;
			}

			~Window()
			{
				glfwDestroyWindow(m_nativeWindow);
				glfwTerminate();

			}

			GLFWwindow* GetHandle()
			{
				return m_nativeWindow;
			}

	
		private:
			Window();
			
			bool isMouseRaw = false;
			GLFWwindow* m_nativeWindow;
			std::map<size_t, std::unique_ptr<ISystem>> m_systemStorage;
			
			void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
			void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
			void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
			//! Events
		public:
			GNF::Common::Event::Event<MouseMoveEventArgs> OnMouseMove;
			GNF::Common::Event::Event<KeyPressedEventArgs> KeyPressed;
			GNF::Common::Event::Event<MousePressedEventArgs> MousePressed;
			//! Static Members
		private:
			inline static std::unique_ptr<Window> g_instance;

	};
}