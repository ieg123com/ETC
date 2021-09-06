#pragma once
#include "IMessage.h"
#include "kernel/Entity.h"


namespace Model
{

	class IMActorRpcHandler :
		public IMSystemHandler
	{
	public:
		virtual void Handle(const std::shared_ptr<GEntity>& unit, const char* data, const size_t len) = 0;
		
		virtual const Type GetRequestType() const = 0;
		virtual const Type GetResponseType() const = 0;
	};


	template<typename T,typename Request,typename Response>
	class MActorRpcHandler :
		public IMActorRpcHandler
	{
	public:
		static_assert(std::is_base_of<IActorRequest, Request>::value,
			"The Request type in MActorRpcHandler needs needs to be inherited from 'IActorRequest'");
		static_assert(std::is_base_of<IActorResponse, Response>::value,
			"The Response type in MActorRpcHandler needs needs to be inherited from 'IActorResponse'");
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
	};

}