#pragma once
#include "IMActorHandler.h"
#include "kernel/Entity.h"




template<typename T, typename Request, typename Response>
class AMActorRpcHandler :
	public IMActorHandler
{
public:
	static_assert(std::is_base_of<IActorRequest, Request>::value,
		"The Request type in MActorRpcHandler needs needs to be inherited from 'IActorRequest'");
	static_assert(std::is_base_of<IActorResponse, Response>::value,
		"The Response type in MActorRpcHandler needs needs to be inherited from 'IActorResponse'");
	virtual void Handle(const std::shared_ptr<GEntity>& entity, IMessage* message, FMPReply& reply) override
	{
		try
		{
			Request* request = dynamic_cast<Request*>(message);
			if (request == nullptr)
			{
				throw std::exception(std::format("转换消息类型失败: %s => %s",
					message->GetType().full_name(),
					typeof(Request).full_name()).c_str());
			}
			auto unit = std::dynamic_pointer_cast<T>(entity);
			if (unit == nullptr)
			{
				throw std::exception(std::format(
					"转换对象类型失败: %s => %s",
					entity->GetObjectType().GetName(),
					typeof(T).full_name()
				).c_str());
			}

			Response response;

			FMReply areply = [&] {
				reply(&response);
			};
			try {
				Run(unit, *request, response, areply);
			}
			catch (std::exception& e)
			{
				LOG_ERROR("AMActorRpcHandler error: 处理消息出错:{} {}",
					typeof(Request).full_name(),
					e.what());
				response.SetError((int32_t)ETC_ERR::HandleActorRpcMessageException);
				response.SetMessage(std::gb2312_to_utf8(e.what()));
				areply();
			}
			catch (...)
			{
				LOG_ERROR("AMActorRpcHandler error: 处理消息出错:{} 未知错误",
					typeof(Request).full_name());
				response.SetError((int32_t)ETC_ERR::HandleActorRpcMessageException);
				response.SetMessage(std::gb2312_to_utf8("未知错误"));
				areply();
			}
		}
		catch (std::exception& e)
		{
			LOG_ERROR("AMActorRpcHandler error: 解析消息失败:{} {}",
				typeof(Request).full_name(),
				e.what());
		}
		catch (...)
		{
			LOG_ERROR("AMActorRpcHandler error: 解析消息失败:{} 未知错误",
				typeof(Request).full_name());
		}

		
	}

	virtual void Run(const std::shared_ptr<T>& unit, Request& request, Response& response,FMReply& reply) = 0;

	virtual const Type GetRequestType() const override { return typeof(Request); }
	virtual const Type GetResponseType() const override { return typeof(Response); }
};
