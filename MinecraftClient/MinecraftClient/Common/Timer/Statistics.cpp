#include "Statistics.h"

#include <boost/chrono.hpp>

namespace GNF::Common::Timer
{
	Statistics::Statistics()
	{
		m_timer = new boost::timer::cpu_timer();

	}
	int Statistics::GetFPS()
	{
		m_currentDelta = GetDeltaTime();
		m_frameCount++;
		if (m_currentDelta - m_lastTime > 1000.0f)
		{
			int frameCount = m_frameCount;
			m_frameCount = 0;
			m_lastTime += 1000.0f;
			
			return frameCount;
		}
		return -1;
	}
	float Statistics::GetDeltaTime()
	{
		return boost::chrono::duration_cast<boost::chrono::duration<double, boost::milli>>(boost::chrono::nanoseconds(m_timer->elapsed().wall)).count();
	}
	void Statistics::Reset()
	{		
	}
	void Statistics::Start()
	{
		m_timer->start();
	}
	void Statistics::Stop()
	{
		m_timer->stop();
	}
	bool Statistics::IsStopped()
	{
		return m_timer->is_stopped();
	}
}