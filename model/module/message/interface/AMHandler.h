#pragma once
#include <memory>
#include "google/protobuf/message.h"
#include "etc/kernel/Entity.h"
#include "IMHandler.h"




template<typename Request>
class AMHandler :
	public IMHandler
{
public:
	static_assert(std::is_base_of<IMessage, Request>::value,
		"The Request type in MessageHandler needs needs to be inherited from 'IMessage'");
	virtual void Handle(const std::shared_ptr<Session>& session, IMessage* message) override
	{
		Run(session, *(Request*)message);
	}

	virtual void Run(const std::shared_ptr<Session>& session, Request& message) = 0;

	virtual const Type GetRequestType() const override { return typeof(Request); }
	virtual const Type GetResponseType() const override { return typeof(IMessage); }
};










