#pragma once
#include "IMessage.h"


namespace Model
{

	template<typename T>
	class IActorRpcMessageSystem :
		public IMessage 
	{
	public:
		virtual void Handle(const std::shared_ptr<GEntity>& unit, const char* data, const size_t len) = 0;

	};


	template<typename T,typename Request,typename Response>
	class ActorRpcMessageSystem :
		public IActorRpcMessageSystem<T>
	{
	public:
		virtual void Handle(const std::shared_ptr<GEntity>& unit, const char* data, const size_t len) override
		{
			Request request;
			Response response;
			if (!request.ParseFromArray(data, len))
			{
				throw std::exception("��������ʧ�ܣ�");
			}
			Run(std::dynamic_pointer_cast<T>(unit), request, response);
		}

		virtual void Run(const std::shared_ptr<T>& unit, Request& request, Response& response) = 0;

		virtual const Type GetRequestType() const override { return typeof(Request); }
		virtual const Type GetResponseType() const override { return typeof(Response); }
	};

}