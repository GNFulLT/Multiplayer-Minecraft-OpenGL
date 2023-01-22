#pragma once

#include <shared_utils/Mouse/IMouse.h>
#include <shared_utils/Logging/ILogger.h>
namespace GNF::OpenGL::Mouse
{
	class GLFW_Mouse : public SU::Mouse::IMouse
	{
		public:
			GLFW_Mouse(SU::Logging::ILogger* logger);

			virtual const glm::vec2 GetMousePos() override;
			virtual const glm::vec2 GetPrevMousePos() override;
			void SetMousePos(float posX, float posY);
			virtual bool IsMouseKeyPressing(SU::Mouse::MOUSE_KEY key) override;

			void MouseKeyPressed(int button);
			void MouseKeyReleased(int button);

			static SU::Mouse::MOUSE_KEY GLFW_MOUSE_KEY_TO_GNF_MOUSE_KEY(SU::Logging::ILogger* logger,int button);
		private:
			glm::vec2 m_mousePos;
			glm::vec2 m_prevMousePos;
			bool m_mouseKeys[SUPPORTED_MOUSE_KEY_NUM];
			SU::Logging::ILogger* m_logger;
	};
}