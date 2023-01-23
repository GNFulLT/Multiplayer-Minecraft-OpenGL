#include "../../include/opengl_utils/Keyboard/Glfw_keyboard.h"
#include <GLFW/glfw3.h>
namespace GNF::OpenGL::Keyboard
{
	GLFW_Keyboard::GLFW_Keyboard(SU::Logging::ILogger* logger) : m_logger(logger)
	{
		for (int i = 0; i < SUPPORTED_KEY_NUM; i++)
		{
			keys[ i ] = false;
		}
	}

	bool GLFW_Keyboard::IsKeyPressed(SU::Keyboard::KEY_CODE code)
	{
		return keys[code];
	}

	void GLFW_Keyboard::KeyPressed(int keyCode)
	{
		keys[GLFW_KEYCODE_TO_GNF_KEYCODE(m_logger,keyCode)] = true;
	}

	void GLFW_Keyboard::KeyReleased(int keyCode)
	{
		keys[GLFW_KEYCODE_TO_GNF_KEYCODE(m_logger,keyCode)] = false;
	}

	SU::Keyboard::KEY_CODE GLFW_Keyboard::GLFW_KEYCODE_TO_GNF_KEYCODE(SU::Logging::ILogger* logger,int keyCode)
	{
		switch (keyCode)
		{
			case GLFW_KEY_A:
				return SU::Keyboard::KEY_A;
			case GLFW_KEY_B:
				return SU::Keyboard::KEY_B;
			case GLFW_KEY_C:
				return SU::Keyboard::KEY_C;
			case GLFW_KEY_D:
				return SU::Keyboard::KEY_D;
			case GLFW_KEY_E:
				return SU::Keyboard::KEY_E;
			case GLFW_KEY_F:
				return SU::Keyboard::KEY_F;
			case GLFW_KEY_G:
				return SU::Keyboard::KEY_G;
			case GLFW_KEY_H:
				return SU::Keyboard::KEY_H;
			case GLFW_KEY_I:
				return SU::Keyboard::KEY_I;
			case GLFW_KEY_J:
				return SU::Keyboard::KEY_J;
			case GLFW_KEY_K:
				return SU::Keyboard::KEY_K;
			case GLFW_KEY_L:
				return SU::Keyboard::KEY_L;
			case GLFW_KEY_M:
				return SU::Keyboard::KEY_M;
			case GLFW_KEY_N:
				return SU::Keyboard::KEY_N;
			case GLFW_KEY_O:
				return SU::Keyboard::KEY_O;
			case GLFW_KEY_P:
				return SU::Keyboard::KEY_P;
			case GLFW_KEY_R:
				return SU::Keyboard::KEY_R;
			case GLFW_KEY_S:
				return SU::Keyboard::KEY_S;
			case GLFW_KEY_T:
				return SU::Keyboard::KEY_T;
			case GLFW_KEY_U:
				return SU::Keyboard::KEY_U;
			case GLFW_KEY_V:
				return SU::Keyboard::KEY_V;
			case GLFW_KEY_Y:
				return SU::Keyboard::KEY_Y;
			case GLFW_KEY_X:
				return SU::Keyboard::KEY_X;
			case GLFW_KEY_W:
				return SU::Keyboard::KEY_W;
			case GLFW_KEY_Z:
				return SU::Keyboard::KEY_Z;
			case GLFW_KEY_UP:
				return SU::Keyboard::KEY_UP;
			case GLFW_KEY_DOWN:
				return SU::Keyboard::KEY_DOWN;
			case GLFW_KEY_RIGHT:
				return SU::Keyboard::KEY_RIGHT;
			case GLFW_KEY_LEFT:
				return SU::Keyboard::KEY_LEFT;
			case GLFW_KEY_0:
				return SU::Keyboard::KEY_0;
			case GLFW_KEY_1:
				return SU::Keyboard::KEY_1;
			case GLFW_KEY_2:
				return SU::Keyboard::KEY_2;
			case GLFW_KEY_3:
				return SU::Keyboard::KEY_3;
			case GLFW_KEY_4:
				return SU::Keyboard::KEY_4;
			case GLFW_KEY_5:
				return SU::Keyboard::KEY_5;
			case GLFW_KEY_6:
				return SU::Keyboard::KEY_6;
			case GLFW_KEY_7:
				return SU::Keyboard::KEY_7;
			case GLFW_KEY_8:
				return SU::Keyboard::KEY_8;
			case GLFW_KEY_9:
				return SU::Keyboard::KEY_9;
			default:
				logger->Critical("Unknown Keyboard Key Pressed Return Z");
				return SU::Keyboard::KEY_Z;
		}
	}
}