#include "TimerComponent.h"
#include "Game.h"


TimerComponent* TimerComponent::Instance = nullptr;

TimerComponent::TimerComponent()
{
	CanEverAwake = true;
	CanEverUpdate = true;
}

void TimerComponent::Awake()
{
	TimerComponent::Instance = this;
}

void TimerComponent::Update()
{
	int64_t now_time = Game::Time().NowServerMilliseconds();

	std::pair<int64_t, std::function<void()>> timer;
	while (!m_timer_enter.empty())
	{
		timer = std::move(m_timer_enter.front());
		m_timer_enter.pop();
		m_timers[now_time + timer.first].emplace_back(timer.second);
	}

	auto iter = m_timers.begin();
	while (iter != m_timers.end())
	{
		if (iter->first <= now_time)
		{
			for (auto& callback : iter->second) callback();
			iter = m_timers.erase(iter);
			continue;
		}
		++iter;
	}
}




