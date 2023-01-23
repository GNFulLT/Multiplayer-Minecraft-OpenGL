#pragma once

#include "shared_utils/Keyboard/IKeyboard.h"
#include <shared_utils/Logging/ILogger.h>

namespace GNF::OpenGL::Keyboard
{
	class GLFW_Keyboard : public SU::Keyboard::IKeyboard
	{
	public:
		GLFW_Keyboard(SU::Logging::ILogger* logger);
		virtual ~GLFW_Keyboard() = default;

		virtual bool IsKeyPressed(SU::Keyboard::KEY_CODE code) override;
		
		void KeyPressed(int keyCode);
		void KeyReleased(int keyCode);
		static SU::Keyboard::KEY_CODE GLFW_KEYCODE_TO_GNF_KEYCODE(SU::Logging::ILogger* logger,int keyCode);


	private:
		bool keys[SUPPORTED_KEY_NUM];
		SU::Logging::ILogger* m_logger;
	};
}