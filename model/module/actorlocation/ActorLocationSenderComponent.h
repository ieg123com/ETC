#pragma once
#include "module/message.h"


class ActorLocationSender;


// 带有地址的Actor消息调用组件
class ActorLocationSenderComponent:
	public Component
{
	class rpc_exception :
		public ::std::exception
	{
	public:
		ETC_ERR Error;
		rpc_exception(const ETC_ERR error,char const* const message) : Error(error), ::std::exception(message) {}
	};


public:
	static ActorLocationSenderComponent* Instance;

	static const time_t TIMEOUT_TIME = 60 * 1000;

	int64_t CheckTimer;

	std::shared_ptr<ActorLocationSender> GetOrCreate(const ID key);

	void Remove(const ID key);



	void Send(const ID key,const std::shared_ptr<IActorRequest>& message);







private:

	std::shared_ptr<IActorResponse> __Call(const ID key, const std::shared_ptr<IActorRequest>& message);

};


