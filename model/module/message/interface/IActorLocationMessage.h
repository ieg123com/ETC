#pragma once
#include "IActorMessage.h"
#include "model/proto/EtcMsg.pb.h"


namespace Model
{

	class IMActorLocationHandler :	
		public IMActorHandler
	{
	public:

	};


	template<typename T, typename Request>
	class MActorLocationHandler :
		public IMActorLocationHandler
	{
	public:
		static_assert(std::is_base_of<IActorLocationMessage, Request>::value,
			"The Request type in MActorLocationHandler needs needs to be inherited from 'IActorLocationMessage'");

		virtual void Handle(const std::shared_ptr<Session>& session, const char* data, const size_t len) override
		{
			Request request;
			if (!request.ParseFromArray(data, len))
			{
				throw std::exception("½âÎöÊý¾ÝÊ§°Ü£¡");
			}
			Run(std::dynamic_pointer_cast<T>(unit), request);
		}

		virtual void Run(const std::shared_ptr<T>& unit, Request& request) = 0;

		virtual const Type GetRequestType() const override { return typeof(Request); }
		virtual const Type GetResponseType() const override { return typeof(ActorResponse); }

	};

}