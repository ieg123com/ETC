#pragma once
#include <stdint.h>
#include <corecrt.h>
#include "coroutine.h"
#include "module/message/MessageDefines.h"



class ActorMessageSender
{
	int64_t m_actor_id;
	time_t	m_last_time;
	
	std::shared_ptr<IMessage> m_proto_request;
	
	co::Channel<std::shared_ptr<IResponse>>	m_proto_request;



};