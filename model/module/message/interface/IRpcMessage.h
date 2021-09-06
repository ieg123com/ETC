#pragma once
#include "IMessage.h"
#include "etc/etc_err.h"

namespace Model
{
	class IMRpcHandler:
		public IMSystemHandler
	{
	public:

		virtual void Handle(const std::shared_ptr<Session>& session, IRequest* request) = 0;
	};


	template<typename Request,typename Response>
	class MRpcHandler :
		public IMRpcHandler
	{
	public:
		static_assert(std::is_base_of<IRequest, Request>::value,
			"The Request type in MRpcHandler needs needs to be inherited from 'IRequest'");
		static_assert(std::is_base_of<IResponse, Response>::value,
			"The Response type in MRpcHandler needs needs to be inherited from 'IResponse'");

		virtual void Handle(const std::shared_ptr<Session>& session, IRequest* request) override
		{
			try
			{
				Response response;

				ObjectID object_id = session->GetObjectID();

				std::function<void()> reply = [&] {
					// 等回调回来,session可以已经断开了,所以需要判断session ObjectId是否一样
					if (session->GetObjectID() != object_id)
					{
						return;
					}
					response.set_rpcid(request->GetRpcId());
					
					session->Reply(&response);
				};

				try {
					Run(session, *(Request*)request, response,reply);
				}
				catch (std::exception& e)
				{
					LOG_ERROR("处理消息失败:{} {}",
						typeof(Request).full_name(),
						e.what());
					response.set_error((int32_t)ETC_ERR::HandleRpcMessageException);
					response.set_message(e.what());
					reply();
				}
				catch (...)
				{
					LOG_ERROR("处理消息失败:{} 未知错误",
						typeof(Request).full_name());
					response.set_error((int32_t)ETC_ERR::HandleRpcMessageException);
					response.set_message("未知错误");
					reply();
				}
			}
			catch (std::exception& e)
			{
				LOG_ERROR("解析消息失败:{} {}",
					typeof(Request).full_name(),
					e.what());
			}
			catch (...)
			{
				LOG_ERROR("解析消息失败:{} 未知错误",
					typeof(Request).full_name());
			}
		}

		virtual void Run(const std::shared_ptr<Session>& session, Request& request, Response& response, std::function<void()>& reply) = 0;

		virtual const Type GetRequestType() const override { return typeof(Request); }
		virtual const Type GetResponseType() const override { return typeof(Response); }

	};


}
