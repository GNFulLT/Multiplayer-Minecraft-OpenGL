#include "InputSystem.h"


namespace GNF::Common::Input
{
	InputSystem::InputSystem()
	{
		for (int i = 0; i < KEYSIZE; i++)
		{
			m_keys[i] = false;
		}
		for (int i = 0; i < MOUSE_KEY_SIZE; i++)
		{
			m_mouseKeys[i] = false;
		}
	}
	void InputSystem::MouseMoved(int x, int y)
	{
		m_prevMouseState.posx = m_mouseState.posx;
		m_prevMouseState.posy = m_mouseState.posy;
		m_mouseState.posx = x;
		m_mouseState.posy = y;
	}
	void InputSystem::GetMouseState(const MouseState** const state)
	{
		(*state) = &m_mouseState;
	}
	void InputSystem::GetPrevMouseState(const MouseState** const state)
	{
		(*state) = &m_prevMouseState;

	}
	void InputSystem::GetPrevCurrMouseState(const MouseState** const prev_state, const MouseState** const curr_state)
	{
		(*curr_state) = &m_mouseState;
		(*prev_state) = &m_prevMouseState;

	}
	void InputSystem::MouseKeyPressed(unsigned int mouseKeyCode)
	{
		m_mouseKeys[mouseKeyCode] = true;
	}
	void InputSystem::MouseKeyReleased(unsigned int mouseKeyCode)
	{
		m_mouseKeys[mouseKeyCode] = false;
	}
	bool InputSystem::IsMouseKeyPressed(unsigned int mouseKeyCode)
	{
		return m_mouseKeys[mouseKeyCode];
	}
	void InputSystem::KeyPressed(unsigned int keyCode)
	{
		m_keys[keyCode] = true;
	}

	void InputSystem::KeyReleased(unsigned int keyCode)
	{
		m_keys[keyCode] = false;
	}
	bool InputSystem::IsKeyPressing(unsigned int keyCode)
	{
		return m_keys[keyCode];
	}
}