#pragma once

#include <boost/timer/timer.hpp>



namespace GNF::Common::Timer
{
	class Statistics
	{
	public:
		Statistics();

		int GetFPS();

		float GetDeltaTime();

		void Reset();

		void Start();

		void Stop();

		bool IsStopped();

		~Statistics()
		{
			if (m_timer != nullptr)
				delete m_timer;
		}
	private:
		boost::timer::cpu_timer* m_timer;
		
		uint_least64_t prevMilliSecond;
		uint_least64_t currMilliSecond;


		float m_currentDelta = 0;
		float m_lastTime =0 ;
		int m_frameCount = 0;
	};
}