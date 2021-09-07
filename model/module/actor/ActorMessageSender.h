#pragma once
#include <stdint.h>
#include <corecrt.h>
#include "coroutine.h"
#include <queue>
#include "etc/etc.h"
#include "module/message/MessageDefines.h"
#include "base/single/ISingleton.h"



class ActorMessageSender
{
	friend class ActorMessageSenderPool;
	ActorMessageSender():m_proto_response(1){}
public:
	int64_t m_actor_id;
	time_t	m_create_time;
	
	std::shared_ptr<IMessage> m_proto_request;
	
	co::Channel<std::shared_ptr<IActorResponse>>	m_proto_response;



};


class ActorMessageSenderPool:
	public ISingleton<ActorMessageSenderPool>
{
	std::queue<ActorMessageSender*>	m_pool;
	// 为 true 关闭时，将不会回收实例
	bool m_closed;

	ActorMessageSenderPool() {
		m_closed = false;
	}
public:
	

	std::shared_ptr<ActorMessageSender> Fetch(int64_t actor_id,const std::shared_ptr<IMessage>& message){
		ActorMessageSender* instance;
		if (m_pool.empty())
		{
			instance = new ActorMessageSender();
		}
		else {
			instance = m_pool.front();
			m_pool.pop();
		}
		instance->m_actor_id = actor_id;
		instance->m_proto_request = message;
		instance->m_create_time = Game::Time().NowServerMilliseconds();
		return std::shared_ptr<ActorMessageSender>(instance, ActorMessageSenderPool::__Recycle);
	}

	// 关闭服务器时调用
	void Close() {
		m_closed = true;
		while (!m_pool.empty())
		{
			delete m_pool.front();
			m_pool.pop();
		}
	}

private:

	static void __Recycle(ActorMessageSender* instance) {
		if (ActorMessageSenderPool::Instance().m_closed)return;
		ActorMessageSenderPool::Instance().m_pool.push(instance);
	}
};