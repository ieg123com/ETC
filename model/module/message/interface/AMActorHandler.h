#pragma once
#include "IMActorHandler.h"
#include "model/proto/EtcMsg.pb.h"






template<typename T, typename Request>
class AMActorHandler :
	public IMActorHandler
{
public:
	static_assert(std::is_base_of<IActorMessage, Request>::value,
		"The Request type in MActorHandler needs needs to be inherited from 'IActorMessage'");

	virtual void Handle(const std::shared_ptr<GEntity>& entity, IMessage* message, FMPReply& reply) override
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

