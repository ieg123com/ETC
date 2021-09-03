#pragma once
#include "IMessage.h"
#include "kernel/Entity.h"


namespace Model
{

	class IMActorRpcHandler :
		public IMessage 
	{
	public:
		virtual void Handle(const std::shared_ptr<GEntity>& unit, const char* data, const size_t len) = 0;
		
		virtual const Type GetRequestType() const = 0;
		virtual const Type GetResponseType() const = 0;
		virtual FMRequestParse GetRequestParse()const = 0;
		virtual FMResponseParse GetResponseParse()const = 0;
		virtual FMResetResponse GetResetResponse()const = 0;
	};


	template<typename T,typename Request,typename Response>
	class MActorRpcHandler :
		public IMActorRpcHandler
	{
	public:
		virtual void Handle(const std::shared_ptr<GEntity>& unit, const char* data, const size_t len) override
		{
			Request request;
			Response response;
			if (!request.ParseFromArray(data, len))
			{
				throw std::exception("½âÎöÊý¾ÝÊ§°Ü£¡");
			}
			Run(std::dynamic_pointer_cast<T>(unit), request, response);
		}

		virtual void Run(const std::shared_ptr<T>& unit, Request& request, Response& response) = 0;

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