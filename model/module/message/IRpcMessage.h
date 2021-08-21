#pragma once
#include "IMessage.h"


namespace Model
{
	class IRpcMessageSystem:
		public IMessage
	{
	public:

		virtual void Handle(const std::shared_ptr<Session>& session, const char* data, const size_t len) = 0;
	};


	template<typename Request,typename Response>
	class RpcMessageSystem :
		public IRpcMessageSystem
	{
	public:
		virtual void Handle(const std::shared_ptr<Session>& session, const char* data, const size_t len) override
		{
			Request request;
			Response response;
			if (!request.ParseFromArray(data, len))
			{
				throw std::exception("½âÎöÊý¾ÝÊ§°Ü£¡");
			}


			Run(session, request, response);
		}

		virtual void Run(const std::shared_ptr<Session>& session, Request& request, Response& response) = 0;

		virtual const Type GetRequestType() const override { return typeof(Request); }
		virtual const Type GetResponseType() const override { return typeof(Response); }
	};


}
