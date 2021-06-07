#pragma once
#include <map>
#include <vector>
#include <queue>
#include <functional>
#include "Component.h"


// ��ʱ��
class TimerComponent:
	public Component
{
public:
	TimerComponent();

	static TimerComponent* Instance;

// 	TimerComponent* GetInstance()
// 	{
// 		static TimerComponent* Instance = nullptr;
// 		return Instance;
// 	}
protected:
	virtual void Awake() override;

	virtual void Update() override;

public:

	// ע��ָ��ʱ��ص�
	template<typename T>
	void RegisterTimeCallBack(const int64_t time,T&& t) {
		m_timer_enter.emplace(time, t);
	}


private:

	std::map<int64_t, std::vector<std::function<void()>>>	m_timers;

	std::queue<std::pair<int64_t, std::function<void()>>>	m_timer_enter;


};