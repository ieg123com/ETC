#pragma once
#include "IMessage.h"
#include "model/proto/EtcMsg.pb.h"




namespace Model
{
	class Unit;

	class IMActorHandler :
		public IMSystemHandler
	{
	public:
		virtual void Handle(const std::shared_ptr<Session>& session, const char* data, const size_t len) = 0;

	};

	template<typename T,typename Request>
	class MActorHandler :
		public IMActorHandler
	{
	public:
		static_assert(std::is_base_of<IActorMessage, Request>::value,
			"The Request type in MActorHandler needs needs to be inherited from 'IActorMessage'");

		virtual void Handle(const std::shared_ptr<Session>& session, const char* data, const size_t len) override
		{
			Request request;
			if (!request.ParseFromArray(data, len))
			{
				throw std::exception("½âÎöÊý¾ÝÊ§°Ü£¡");
			}
			Run(std::dynamic_pointer_cast<T>(unit), request);
		}

		virtual void Run(const std::shared_ptr<T>& unit, Request& message) = 0;

		virtual const Type GetRequestType() const override { return typeof(Request); }
		virtual const Type GetResponseType() const override { return typeof(ActorResponse); }
	};


}
