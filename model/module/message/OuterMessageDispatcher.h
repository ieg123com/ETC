#pragma once
#include "IMessageDispatcher.h"



// 外网消息分发
class OuterMessageDispatcher :
	public IMessageDispatcher
{
public:

	virtual void Dispatch(const std::shared_ptr<Session>& session, const char* data, const size_t len) override;
};