#pragma once
#include "IMActorHandler.h"





template<typename T, typename Request, typename Response>
class MActorLocationRpcHandler :
	public IMActorHandler
{
public:
	static_assert(std::is_base_of<IActorLocationRequest, Request>::value,
		"The Request type in MActorLocationRpcHandler needs needs to be inherited from 'IActorLocationRequest'");
	static_assert(std::is_base_of<IActorLocationResponse, Response>::value,
		"The Response type in MActorLocationRocHandler needs needs to be inherited from 'IActorLocationRepsonse'");

	virtual void Handle(const std::shared_ptr<GEntity>& entity, IMessage* message, FMPReply& reply) override
	{
		Request request;
		Response response;
		if (!request.ParseFromArray(data, len))
		{
			throw std::exception("½âÎöÊý¾ÝÊ§°Ü£¡");
		}
		Run(std::dynamic_pointer_cast<T>(unit), request, response);
	}

	virtual void Run(const std::shared_ptr<T>& unit, Request& request, Response& response,FMReply& reply) = 0;

	virtual const Type GetRequestType() const override { return typeof(Request); }
	virtual const Type GetResponseType() const override { return typeof(Response); }

};

