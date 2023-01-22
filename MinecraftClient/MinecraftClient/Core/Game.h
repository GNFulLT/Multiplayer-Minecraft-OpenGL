#pragma once

#include <memory>
#include <stack>
#include <memory>

#include "States/IState.h"
#include <opengl_utils/Windowing/Window.h>
#include <shared_utils/Logging/Logger_1.h>

namespace GNF::Core
{
	class Game
	{
		public:
			static Game* Build()
			{
				g_instance.reset(new Game());
				return GetInstance();
			}
			inline static Game* GetInstance()
			{
				return g_instance.get();
			}
			
			void Init();

			void Run();
		private:
			std::stack<std::unique_ptr<States::IState>> m_states;
			std::unique_ptr<SU::Windowing::IWindow> m_window;
		private:
			inline static std::unique_ptr<Game> g_instance;
	};
}