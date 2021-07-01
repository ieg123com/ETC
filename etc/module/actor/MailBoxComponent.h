/**
 * @file	MailBoxComponent.h
 * @author	ieg123
 * @date	2021-06-30
 * @brief	内部通信邮箱组件，用于处理内部 Actor 消息
 */
#pragma once
#include "Component.h"
#include "coroutine.h"
#include <functional>


/** @brief	内部通信邮箱组件 */
class MailBoxComponent:
	public Component
{
public:
	MailBoxComponent() {
		CanEverAwake = true;
	}




protected:

	virtual void Awake() override;

	virtual void Destroy() override;

private:

	/**
	 * @brief	开始监听任务
	 */
	void __StartLoop();

	/**
	 * @brief	停止监听任务
	 */
	void __StopLoop();

	/** @brief 当前以停止监听任务 */
	bool	m_stopped;

	/** @brief Actor 任务队列 */
	co::Channel<std::function<void()>>	m_channel;

};