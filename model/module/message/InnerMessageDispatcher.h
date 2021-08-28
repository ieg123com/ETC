#pragma once
#include "IMessageDispatcher.h"


// 内网消息分发
class InnerMessageDispatcher:
	public IMessageDispatcher
{
public:

	virtual void Dispatch(const std::shared_ptr<Session>& session, const char* data, const size_t len) override;


};
