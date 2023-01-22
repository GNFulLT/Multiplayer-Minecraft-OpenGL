#pragma once

#include "../IGameThing.h"

namespace GNF::Core::States
{
	class IState : public IGameThing
	{
		public:
			virtual ~IState() = default;
			
			virtual bool IsWantedQuit()
			{
				return m_wantedQuit;
			}

			virtual void CheckIfWantedQuit() = 0;
			
		protected:
			bool m_wantedQuit = false;
	};
}