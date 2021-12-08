#pragma once
#include "IMSystemHandler.h"
#include "net/Session.h"
#include "kernel/Entity.h"
#include "module/message/MessageDefines.h"




class IMActorHandler :
	public IMSystemHandler
{
public:
	virtual void Handle(const std::shared_ptr<GEntity>& entity, IMessage* message, const FMPReply& reply) = 0;

};