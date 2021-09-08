#pragma once
#include "IMActorHandler.h"
#include "kernel/Entity.h"




template<typename T, typename Request, typename Response>
class AMActorRpcHandler :
	public IMActorHandler
{
public:
	static_assert(std::is_base_of<IActorRequest, Request>::value,
		"The Request type in MActorRpcHandler needs needs to be inherited from 'IActorRequest'");
	static_assert(std::is_base_of<IActorResponse, Response>::value,
		"The Response type in MActorRpcHandler needs needs to be inherited from 'IActorResponse'");
	virtual void Handle(const std::shared_ptr<GEntity>& entity, IMessage* message, FMPReply& reply) override
	{
		Request* request = dynamic_cast<Request*>(message);
		Response response;

		FMReply areply = [&] {
			reply(&response);
		};

		Run(std::dynamic_pointer_cast<T>(entity), *request, response, areply);
	}

	virtual void Run(const std::shared_ptr<T>& unit, Request& request, Response& response,FMReply& reply) = 0;

	virtual const Type GetRequestType() const override { return typeof(Request); }
	virtual const Type GetResponseType() const override { return typeof(Response); }
};
