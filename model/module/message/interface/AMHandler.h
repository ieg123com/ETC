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
				throw std::exception(std::format("转换消息类型失败: %s => %s",
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
				LOG_ERROR("AMHandler error: 处理消息出错:{} {}",
					typeof(Request).full_name(),
					e.what());
			}
			catch (...)
			{
				LOG_ERROR("AMHandler error: 处理消息出错:{} 未知错误",
					typeof(Request).full_name());
			}
		}
		catch (std::exception& e)
		{
			LOG_ERROR("AMHandler error: 解析消息失败:{} {}",
				typeof(Request).full_name(),
				e.what());
		}
		catch (...)
		{
			LOG_ERROR("AMHandler error: 解析消息失败:{} 未知错误",
				typeof(Request).full_name());
		}
		
	}

	virtual void Run(const std::shared_ptr<Session>& session, Request& message) = 0;

	virtual const Type GetRequestType() const override { return typeof(Request); }
	virtual const Type GetResponseType() const override { return typeof(IMessage); }
};










