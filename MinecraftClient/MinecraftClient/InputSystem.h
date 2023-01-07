#pragma once

#include "Common/IInputSystem.h"

namespace GNF::Common::Input
{
	#define KEYSIZE 256
	#define MOUSE_KEY_SIZE 3
	class InputSystem : public IInputSystem
	{
		public:
			InputSystem();
			InputSystem(const InputSystem&) = delete;
			InputSystem& operator = (const InputSystem&) = delete;
			virtual bool IsMouseKeyPressed(unsigned int mouseKeyCode) override;

			virtual bool IsKeyPressing(unsigned int keyCode) override;

			virtual void KeyPressed(unsigned int keyCode) override;

			virtual void KeyReleased(unsigned int keyCode) override;


			virtual void MouseMoved(int x, int y) override;
			virtual void GetMouseState(const MouseState** const state) override;
			virtual void GetPrevMouseState(const MouseState** const state)override;
			virtual void GetPrevCurrMouseState(const MouseState** const prev_state, const MouseState** const curr_state) override;

			virtual void MouseKeyPressed(unsigned int mouseKeyCode) override;
			virtual void MouseKeyReleased(unsigned int mouseKeyCode) override;
		private:
			bool m_keys[KEYSIZE];
			bool m_mouseKeys[MOUSE_KEY_SIZE];
			MouseState m_mouseState;
			MouseState m_prevMouseState;
	};
}