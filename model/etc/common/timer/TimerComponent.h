#pragma once
#include <map>
#include <vector>
#include <queue>
#include <functional>
#include "Component.h"
#include "kernel/Entity.h"

using namespace Model;
// 计时器类型
enum class ETimerType :uint8_t
{
	None,
	Once,		// 执行一次
	Repeated,	// 重复执行
};


class TimerAction :
	public GEntity
{
public:
	using CallBack = std::function<void()>;

	ETimerType TimerType;

	CallBack Callback;
	// 执行时间间隔
	time_t	Time;
};



// 计时器
class TimerComponent :
	public Component
{
public:

	static TimerComponent* Instance;

	void Awake();

	void Update();

public:

	// 注册一次执行的计时器
	int64_t RegisterOnceTimer(const time_t till_time, TimerAction::CallBack& call_back) {
		
	}

	// 注册重复执行的计时器
	int64_t RegisterRepeatedTimer(const time_t till_time, TimerAction::CallBack& call_back) {

	}


	void AddTimer(const time_t till_time, const std::shared_ptr<TimerAction>& timer) {
		m_timers.emplace(timer->InstanceId(), timer);
		m_timerid.emplace(till_time, timer->InstanceId());
	}

	void RemoveTimer(const InstanceID id) {
		
	}

private:
	// key: InstanceId,value: Timer
	// 全部计时器任务
	std::unordered_map<InstanceID,std::shared_ptr<TimerAction>>	m_timers;
	// frist: run time,second: Timer

	// key: time ,value: Timer
	// 记录计时器任务的超时时间
	std::multimap<time_t, InstanceID>		m_timerid;

	std::queue<time_t>			m_timeout_time;
	std::queue<InstanceID>		m_timeout_timerid;

};
