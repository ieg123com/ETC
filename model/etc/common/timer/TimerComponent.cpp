#include "TimerComponent.h"
#include "Game.h"
#include "etc/etc.h"


class TimerActionAwakeSystem :public AwakeSystem<TimerAction, time_t, TimerAction::CallBack&, ETimerType>
{
public:
	virtual void Awake(const std::shared_ptr<TimerAction>& self, time_t time, TimerAction::CallBack& call_back, ETimerType tp)override
	{
		self->Time = time;
		self->Callback = call_back;
		self->TimerType = tp;
	}
};
REF(TimerActionAwakeSystem, ObjectSystem);

class TimerActionDestroySystem :public DestroySystem<TimerAction>
{
public:
	virtual void Destroy(const std::shared_ptr<TimerAction>& self)override
	{
		// TimerAction 销毁后会被对象池回收，
		// 这时其他会被回调变量引用，导致无法销毁
		self->Callback = nullptr;
	}
};





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


class TimerComponentDestroySystem :public DestroySystem<TimerComponent>
{
public:
	virtual void Destroy(const std::shared_ptr<TimerComponent>& self)override
	{
		self->Destroy();
	}
};
REF(TimerComponentDestroySystem, ObjectSystem);


TimerComponent* TimerComponent::Instance = nullptr;


void TimerComponent::Awake()
{
	TimerComponent::Instance = this;
	m_min_time = 0;
}

void TimerComponent::Update()
{
	int64_t now_time = Game::Time().NowServerMilliseconds();
	if (now_time < m_min_time)return;	// 没有计时器需要执行

	time_t k = 0;
	for (auto& item : m_timerid)
	{
		if (item.first != k)
		{
			k = item.first;
			if (k > now_time)
			{
				m_min_time = k;
				break;
			}
			m_timeout_time.push(k);
		}
		m_timeout_timerid.push(item.second);
	}

	while (!m_timeout_time.empty())
	{
		m_timerid.erase(m_timeout_time.front());
		m_timeout_time.pop();
	}

	while (!m_timeout_timerid.empty())
	{
		InstanceID timer_id = m_timeout_timerid.front();
		auto found = m_timers.find(timer_id);
		m_timeout_timerid.pop();
		if (found == m_timers.end())continue;
		try {
			__Run(now_time, found->second);
		}
		catch (std::exception& e)
		{
			LOG_ERROR("Timer error: 执行timer时发生错误,timer_id = {} ({})", timer_id,e.what());
		}
	}
}

void TimerComponent::Destroy()
{
	while (!m_timers.empty())
	{
		auto iter = m_timers.begin();
		auto timer = iter->second;
		m_timers.erase(iter);
		timer->Dispose();
	}
	m_timerid.clear();
	while (!m_timeout_time.empty())m_timeout_time.pop();
	while (!m_timeout_timerid.empty())m_timeout_timerid.pop();

}





int64_t TimerComponent::RegisterOnceTimer(const time_t time,TimerAction::CallBack&& call_back) {
	auto timer = ObjectFactory::CreateWithHost<TimerAction, time_t, TimerAction::CallBack&, ETimerType>(Self(), time, call_back, ETimerType::Once, false);
	AddTimer(Game::Time().NowServerMilliseconds()+time, timer);
	return timer->InstanceId();
}


int64_t TimerComponent::RegisterRepeatedTimer(const time_t time, TimerAction::CallBack&& call_back) {
	auto timer = ObjectFactory::CreateWithHost<TimerAction, time_t, TimerAction::CallBack&, ETimerType>(Self(), time, call_back, ETimerType::Repeated, false);
	AddTimer(Game::Time().NowServerMilliseconds() + time, timer);
	return timer->InstanceId();
}


void TimerComponent::AddTimer(const time_t till_time, const std::shared_ptr<TimerAction>& timer) {
	m_timers.emplace(timer->InstanceId(), timer);
	AddTimer(till_time, timer->InstanceId());
}


void TimerComponent::AddTimer(const time_t till_time, const InstanceID id) {
	m_timerid.emplace(till_time, id);
	if (till_time < m_min_time)
	{
		m_min_time = till_time;
	}
}


void TimerComponent::RemoveTimer(const InstanceID id) {
	auto found = m_timers.find(id);
	if (found == m_timers.end())
	{
		return;
	}
	auto timer_action = found->second;
	m_timers.erase(found);
	timer_action->Dispose();
}


void TimerComponent::__Run(const time_t trigeer_time,const std::shared_ptr<TimerAction>& timer) {
	switch (timer->TimerType)
	{
	case ETimerType::Once:
	{
		auto func = std::move(timer->Callback);
		RemoveTimer(timer->InstanceId());
		func();
		break;
	}	
	case ETimerType::Repeated:
	{
		time_t time = trigeer_time + timer->Time;
		AddTimer(time, timer->InstanceId());
		timer->Callback();
		break;
	}
	}
}
