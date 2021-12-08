#pragma once
#include "IMessageDispatcher.h"


// ������Ϣ�ַ�
class InnerMessageDispatcher:
	public IMessageDispatcher
{
public:

	virtual void Dispatch(const std::shared_ptr<Session>& session, const char* data, const size_t len) override;


};
