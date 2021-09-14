#pragma once
#include "IMActorHandler.h"





template<typename T, typename Request, typename Response>
class AMActorLocationRpcHandler :
	public IMActorHandler
{
public:
	static_assert(std::is_base_of<IActorLocationRequest, Request>::value,
		"The Request type in MActorLocationRpcHandler needs needs to be inherited from 'IActorLocationRequest'");
	static_assert(std::is_base_of<IActorLocationResponse, Response>::value,
		"The Response type in MActorLocationRocHandler needs needs to be inherited from 'IActorLocationRepsonse'");

	virtual void Handle(const std::shared_ptr<GEntity>& entity, IMessage* message, const FMPReply& reply) override
	{
		try {
			Request* request = dynamic_cast<Request*>(message);
			if (request == nullptr)
			{
				throw std::exception(std::format(
					"转换消息类型失败: %s => %s",
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
			catch (std::exception& e) {
				LOG_ERROR("MActorLocationRpcHandler error: 处理消息出错:{} {}",
					typeof(Request).full_name(),
					e.what());
			}
			catch (...) {
				LOG_ERROR("MActorLocationRpcHandler error: 处理消息出错:{} 未知错误",
					typeof(Request).full_name());
			}
		}
		catch (std::exception& e) {
			LOG_ERROR("MActorLocationRpcHandler error: 解析消息失败:{} {}",
				typeof(Request).full_name(),
				e.what());
		}
		catch (...) {
			LOG_ERROR("MActorLocationRpcHandler error: 解析消息失败:{} {}",
				typeof(Request).full_name());
		}
		
	}

	virtual void Run(const std::shared_ptr<T>& unit, Request& request, Response& response,FMReply& reply) = 0;

	virtual const Type GetRequestType() const override { return typeof(Request); }
	virtual const Type GetResponseType() const override { return typeof(Response); }

};

