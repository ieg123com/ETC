#pragma once
#include "IMActorHandler.h"
#include "model/proto/EtcMsg.pb.h"





template<typename T, typename Request>
class MActorLocationHandler :
	public IMActorHandler
{
public:
	static_assert(std::is_base_of<IActorLocationMessage, Request>::value,
		"The Request type in MActorLocationHandler needs needs to be inherited from 'IActorLocationMessage'");

	virtual void Handle(const std::shared_ptr<GEntity>& entity, IMessage* message, const FMPReply& reply) override
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
			ActorResponse response;

			auto unit = std::dynamic_pointer_cast<T>(entity);
			if (unit == nullptr)
			{
				throw std::exception(std::format(
					"转换对象类型失败: %s => %s",
					entity->GetObjectType().GetName(),
					typeof(T).full_name()
				).c_str());
			}

			// 因为这不是一条rpc消息，对方不需要知道有没有执行成功。
			// 提前回复消息，告诉对方消息收到了，地址木的问题。
			reply(&response);

			try
			{
				Run(unit, *request);
			}
			catch (std::exception& e)
			{
				LOG_ERROR("MActorLocationHandler error: 处理消息出错:{} {}",
					typeof(Request).full_name(),
					e.what());
			}
			catch (...)
			{
				LOG_ERROR("MActorLocationHandler error: 处理消息出错:{} 未知错误",
					typeof(Request).full_name());
			}
		}
		catch (std::exception& e)
		{
			LOG_ERROR("MActorLocationHandler error: 解析消息失败:{} {}",
				typeof(Request).full_name(),
				e.what());
		}
		catch (...)
		{
			LOG_ERROR("MActorLocationHandler error: 解析消息失败:{} 未知错误",
				typeof(Request).full_name());
		}
	
	}

	virtual void Run(const std::shared_ptr<T>& unit, Request& request) = 0;

	virtual const Type GetRequestType() const override { return typeof(Request); }
	virtual const Type GetResponseType() const override { return typeof(ActorResponse); }

};
