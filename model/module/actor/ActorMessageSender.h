#pragma once
#include <stdint.h>
#include <corecrt.h>
#include "coroutine.h"
#include <queue>
#include "etc/etc.h"
#include "module/message/MessageDefines.h"
#include "base/single/ISingleton.h"

// ������¼һ��Actor����Ķ���
class ActorMessageSender
{
	friend class ActorMessageSenderPool;
	ActorMessageSender() :ProtoResponse(1) {}
public:

	int64_t ActorId;
	time_t	CreateTime;
	
	std::shared_ptr<IMessage> ProtoRequest;
	
	co::Channel<std::shared_ptr<IActorResponse>>	ProtoResponse;
	// HasException = true��������������쳣����Ҫ�ڵ���ʱ�׳�
	bool HasException;

	std::exception Exception;

	// �����쳣
	void SetException(std::exception& e);

};


class ActorMessageSenderPool:
	public ISingleton<ActorMessageSenderPool>
{

	std::queue<ActorMessageSender*>	m_pool;
	// Ϊ true �ر�ʱ�����������ʵ��
	bool m_closed;

public:
	ActorMessageSenderPool() {
		m_closed = false;
	}

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
		instance->ActorId = actor_id;
		instance->ProtoRequest = message;
		instance->HasException = false;
		instance->CreateTime = Game::Time().NowServerMilliseconds();
		return std::shared_ptr<ActorMessageSender>(instance, ActorMessageSenderPool::__Recycle);
	}

	// �رշ�����ʱ����
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