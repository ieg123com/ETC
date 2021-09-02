#pragma once
#include "IMessage.h"

namespace Model
{
	class IMRpcHandler:
		public IMessage
	{
	public:

		virtual void Handle(const std::shared_ptr<Session>& session, const char* data, const size_t len) = 0;

		virtual FMRequestParse GetRequestParse()const = 0;
		virtual FMResponseParse GetResponseParse()const = 0;
		virtual FMResetResponse GetResetResponse()const = 0;
	};


	template<typename Request,typename Response>
	class MRpcHandler :
		public IMRpcHandler
	{
	public:
		virtual void Handle(const std::shared_ptr<Session>& session, const char* data, const size_t len) override
		{
			try
			{
				Request request;
				Response response;
				if (!request.ParseFromArray(data, len))
				{
					throw std::exception("解析数据失败！");
				}

				ObjectID object_id = session->GetObjectID();

				std::function<void()> reply = [&] {
					// 等回调回来,session可以已经断开了,所以需要判断session ObjectId是否一样
					if (session->GetObjectID() != object_id)
					{
						return;
					}
					response.set_rpcid(request.rpcid());
					
					session->Reply(response);
				};

				try {
					Run(session, request, response,reply);
				}
				catch (std::exception& e)
				{
					LOG_ERROR("处理消息失败:{} {}",
						typeof(Request).class_name(),
						e.what());
					response.set_error(1);
					response.set_message(e.what());
					reply();
				}
				catch (...)
				{
					LOG_ERROR("处理消息失败:{} 未知错误",
						typeof(Request).class_name());
					response.set_error(1);
					response.set_message("未知错误");
					reply();
				}
			}
			catch (std::exception& e)
			{
				LOG_ERROR("解析消息失败:{} {}",
					typeof(Request).class_name(),
					e.what());
			}
			catch (...)
			{
				LOG_ERROR("解析消息失败:{} 未知错误",
					typeof(Request).class_name());
			}
		}

		virtual void Run(const std::shared_ptr<Session>& session, Request& request, Response& response, std::function<void()>& reply) = 0;

		virtual const Type GetRequestType() const override { return typeof(Request); }
		virtual const Type GetResponseType() const override { return typeof(Response); }
		virtual FMRequestParse GetRequestParse()const override {
			return MRequestParse<Request>()();
		}
		virtual FMResponseParse GetResponseParse()const override {
			return MResponseParse<Response>()();
		}
		virtual FMResetResponse GetResetResponse()const override {
			return MResetResponse<Response>()();
		}

	};


}
