#pragma once
#include "IMHandler.h"
#include "etc/etc_err.h"



template<typename Request,typename Response>
class AMRpcHandler :
	public IMHandler
{
public:
	static_assert(std::is_base_of<IRequest, Request>::value,
		"The Request type in MRpcHandler needs needs to be inherited from 'IRequest'");
	static_assert(std::is_base_of<IResponse, Response>::value,
		"The Response type in MRpcHandler needs needs to be inherited from 'IResponse'");

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
			Response response;

			InstanceID instance_id = session->InstanceId();

			FMReply reply = [&] {
				// 等回调回来,session可以已经断开了,所以需要判断session InstanceID是否一样
				if (session->InstanceId() != instance_id)
				{
					return;
				}
				response.set_rpcid(request->GetRpcId());
					
				session->Reply(&response);
			};

			try {
				Run(session, *request, response,reply);
			}
			catch (std::exception& e)
			{
				LOG_ERROR("AMRpcHandler error: 处理消息失败:{} {}",
					typeof(Request).full_name(),
					e.what());
				response.set_error((int32_t)ETC_ERR::HandleRpcMessageException);
				response.set_message(std::gb2312_to_utf8(e.what()));
				reply();
			}
			catch (...)
			{
				LOG_ERROR("AMRpcHandler error: 处理消息失败:{} 未知错误",
					typeof(Request).full_name());
				response.set_error((int32_t)ETC_ERR::HandleRpcMessageException);
				response.set_message(std::gb2312_to_utf8("未知错误"));
				reply();
			}
		}
		catch (std::exception& e)
		{
			LOG_ERROR("AMRpcHandler error: 解析消息失败:{} {}",
				typeof(Request).full_name(),
				e.what());
		}
		catch (...)
		{
			LOG_ERROR("AMRpcHandler error: 解析消息失败:{} 未知错误",
				typeof(Request).full_name());
		}
	}

	virtual void Run(const std::shared_ptr<Session>& session, Request& request, Response& response, FMReply& reply) = 0;

	virtual const Type GetRequestType() const override { return typeof(Request); }
	virtual const Type GetResponseType() const override { return typeof(Response); }

};
