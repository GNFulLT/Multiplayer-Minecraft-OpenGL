#include "../../opengl_utils/include/opengl_utils/Mouse/Glfw_mouse.h"
#include "GLFW/glfw3.h"
namespace GNF::OpenGL::Mouse
{
	GLFW_Mouse::GLFW_Mouse(SU::Logging::ILogger* logger) : m_logger(logger)
	{
		for (int i = 0; i < SUPPORTED_MOUSE_KEY_NUM; i++)
		{
			m_mouseKeys[i] = false;
		}
	}
	const glm::vec2 GLFW_Mouse::GetMousePos()
	{
		return m_mousePos;
	}
	const glm::vec2 GLFW_Mouse::GetPrevMousePos()
	{
		return m_prevMousePos;
	}
	void GLFW_Mouse::SetMousePos(float posX, float posY)
	{
		m_prevMousePos = m_mousePos;
		m_mousePos.x = posX;
		m_mousePos.y = posY;
	}
	bool GLFW_Mouse::IsMouseKeyPressing(SU::Mouse::MOUSE_KEY key)
	{
		return m_mouseKeys[key];
	}
	void GLFW_Mouse::MouseKeyPressed(int button)
	{
		m_mouseKeys[GLFW_MOUSE_KEY_TO_GNF_MOUSE_KEY(m_logger,button)] = true;
	}
	void GLFW_Mouse::MouseKeyReleased(int button)
	{
		m_mouseKeys[GLFW_MOUSE_KEY_TO_GNF_MOUSE_KEY(m_logger,button)] = false;
	}
	SU::Mouse::MOUSE_KEY GLFW_Mouse::GLFW_MOUSE_KEY_TO_GNF_MOUSE_KEY(SU::Logging::ILogger* logger,int button)
	{
		switch (button)
		{
			case GLFW_MOUSE_BUTTON_LEFT:
				return SU::Mouse::MOUSE_LEFT;
			case GLFW_MOUSE_BUTTON_RIGHT:
				return SU::Mouse::MOUSE_RIGHT;
			case GLFW_MOUSE_BUTTON_MIDDLE:
				return SU::Mouse::MOUSE_MIDDLE;
			default:
				logger->Critical("Unknown Mouse Key Pressed return Mouse_Left");
;				return SU::Mouse::MOUSE_LEFT;

		}
	}
}
