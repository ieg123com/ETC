#include "TimerComponent.h"
#include "Game.h"
#include "etc/etc.h"


class TimerActionAwakeSystem :public AwakeSystem<TimerAction, time_t, TimerAction::Action&, ETimerType>
{
public:
	virtual void Awake(const std::shared_ptr<TimerAction>& self, time_t time, TimerAction::Action& call_back, ETimerType tp)override
	{
		self->Time = time;
		self->CallBack = call_back;
		self->TimerType = tp;
	}
};
REF(TimerActionAwakeSystem, ObjectSystem);







class TimerComponentAwakeSystem :public AwakeSystem<TimerComponent>
{
public:
	virtual void Awake(const std::shared_ptr<TimerComponent>& self)override
	{
		self->Awake();
	}
};
REF(TimerComponentAwakeSystem, ObjectSystem);

class TimerComponentUpdateSystem : public UpdateSystem<TimerComponent>
{
public:
	virtual void Update(const std::shared_ptr<TimerComponent>& self) override
	{
		self->Update();
	}
};
REF(TimerComponentUpdateSystem, ObjectSystem);


TimerComponent* TimerComponent::Instance = nullptr;


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

