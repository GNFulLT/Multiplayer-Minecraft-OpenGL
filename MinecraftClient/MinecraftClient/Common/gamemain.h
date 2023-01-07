#pragma once

#include "window.h"
#include <memory>
#include "FPSCamera.h"
#include "IInputSystem.h"
#include "Camera/ICamera.h"
namespace GNF::Common
{
	class GameMain
	{
		public:
			static GameMain* GetInstance();
			static GameMain* Build();
			int Run();

			void MouseMoved(const MouseMoveEventArgs& e);
			void OnKeyPressed(const KeyPressedEventArgs& e);
			void OnMousePressed(const MousePressedEventArgs& e);
			std::unique_ptr<Camera::ICamera> camera;
			Input::IInputSystem* GetInputSystem();
			
		private:
			GameMain();

			bool firstMouse = true;
			double lastX = 0;
			double lastY = 0;
			Window* pWindow;

			std::unique_ptr<Input::IInputSystem> m_inputSystem;
			
		private:
			inline static std::unique_ptr<GameMain> g_game;
	};
}