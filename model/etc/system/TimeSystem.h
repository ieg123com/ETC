#pragma once
#include <stdint.h>
namespace Model
{
	class TimeSystem
	{
	public:
		TimeSystem();

		// 上一帧刷新时间增量 毫秒
		int64_t DeltaTime;


		int64_t NowServerMilliseconds();

		int64_t NowServerSeconds();



	private:
		// 刷新更新时间
		void RefreshLastTime();
	private:
		// 上次更新时间
		int64_t	m_last_time;

		friend class GameSystem;
		friend class MEventSystem;
	};
}