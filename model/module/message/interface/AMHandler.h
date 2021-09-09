#pragma once
#include <memory>
#include "google/protobuf/message.h"
#include "etc/kernel/Entity.h"
#include "IMHandler.h"




template<typename Request>
class AMHandler :
	public IMHandler
{
public:
	static_assert(std::is_base_of<IMessage, Request>::value,
		"The Request type in MessageHandler needs needs to be inherited from 'IMessage'");
	virtual void Handle(const std::shared_ptr<Session>& session, IMessage* message) override
	{
		try
		{
			Request* request = dynamic_cast<Request*>(message);
			if (request == nullptr)
			{
				throw std::exception(std::format("ת����Ϣ����ʧ��: %s => %s",
					message->GetType().full_name(),
					typeof(Request).full_name()
				).c_str());
			}
			try
			{
				Run(session, *request);
			}
			catch (std::exception& e)
			{
				LOG_ERROR("AMHandler error: ������Ϣ����:{} {}",
					typeof(Request).full_name(),
					e.what());
			}
			catch (...)
			{
				LOG_ERROR("AMHandler error: ������Ϣ����:{} δ֪����",
					typeof(Request).full_name());
			}
		}
		catch (std::exception& e)
		{
			LOG_ERROR("AMHandler error: ������Ϣʧ��:{} {}",
				typeof(Request).full_name(),
				e.what());
		}
		catch (...)
		{
			LOG_ERROR("AMHandler error: ������Ϣʧ��:{} δ֪����",
				typeof(Request).full_name());
		}
		
	}

	virtual void Run(const std::shared_ptr<Session>& session, Request& message) = 0;

	virtual const Type GetRequestType() const override { return typeof(Request); }
	virtual const Type GetResponseType() const override { return typeof(IMessage); }
};










