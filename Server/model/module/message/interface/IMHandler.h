#pragma once
#include "IMSystemHandler.h"
#include "net/Session.h"
#include "module/message/MessageDefines.h"



class IMHandler :
	public IMSystemHandler
{
public:
	virtual void Handle(const std::shared_ptr<Session>& session, IMessage* message) = 0;

};