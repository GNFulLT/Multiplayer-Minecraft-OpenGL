#pragma once

#include "ISystem.h"

namespace GNF::Common::Input
{
	struct MouseState
	{
		MouseState()
		{
			posx = 0;
			posy = 0;
		}
		int posx;
		int posy;
	};

	class IInputSystem 
	{
	
		public:
			virtual ~IInputSystem() = default;

			virtual bool IsKeyPressing(unsigned int keyCode) = 0;

			virtual void KeyPressed(unsigned int keyCode) = 0;
			virtual bool IsMouseKeyPressed(unsigned int mouseKeyCode) = 0;

			virtual void KeyReleased(unsigned int keyCode) = 0;

			virtual void MouseMoved(int x, int y) = 0;
			virtual void GetMouseState(const MouseState** const state) = 0;
			virtual void GetPrevMouseState(const MouseState** const state) = 0;
			virtual void GetPrevCurrMouseState(const MouseState** const prev_state, const MouseState** const curr_state) = 0;

			virtual void MouseKeyPressed(unsigned int mouseKeyCode) = 0;
			virtual void MouseKeyReleased(unsigned int mouseKeyCode) = 0;
		private:
	};
}