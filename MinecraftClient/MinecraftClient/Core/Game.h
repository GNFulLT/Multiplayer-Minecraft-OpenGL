#pragma once

#include <memory>
#include <stack>
#include <memory>

#include "States/IState.h"
#include <opengl_utils/Windowing/Window.h>
#include <shared_utils/Logging/Logger_1.h>

#include "../Common/Timer/Statistics.h"

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

			void Update();
			void Render();

			//!: Update Funcs
			void UpdateStatistics();
			void UpdateStates(const float dt);

			void Run();

			~Game();
		private:
			std::stack<std::unique_ptr<States::IState>> m_states;
			std::unique_ptr<SU::Windowing::IWindow> m_window;
			Common::Timer::Statistics m_statistics;
		private:
			inline static std::unique_ptr<Game> g_instance;
	};
}