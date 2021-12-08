#include "TimeSystem.h"
#include <chrono>

namespace Model
{
	TimeSystem::TimeSystem()
	{
		m_last_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
		DeltaTime = 0;
	}

	int64_t TimeSystem::NowServerMilliseconds()
	{
		return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	}

	int64_t TimeSystem::NowServerSeconds()
	{
		return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	}

	// 刷新更新时间
	void TimeSystem::RefreshLastTime()
	{
		int64_t now_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
		DeltaTime = now_time - m_last_time;
		m_last_time = now_time;
	}
}