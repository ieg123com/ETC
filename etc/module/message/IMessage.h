#pragma once
#include <memory>
#include "google/protobuf/message.h"


class Session;

template<typename T>
class IMessage
{
public:

	virtual void Run(std::shared_ptr<Session> session,T& message) = 0;

};


template<typename T>
class RegIMessage
{
public:
	RegIMessage() {

	}
};



#define REGMESSAGE() 0



class TestMessage :
	public IMessage<ddd>
{
public:
	virtual void Run(std::shared_ptr<Session> session, void message) override
	{

	}
};
