#pragma once
#include "IMessage.h"



namespace Model
{
	class Unit;

	template<typename T>
	class IActorMessageSystem :
		public IMessage 
	{
	public:
		virtual void Handle(const std::shared_ptr<T>& unit, const ::google::protobuf::Message* message) = 0;
	};

	template<typename T,typename Request>
	class ActorMessageSystem :
		public IActorMessageSystem<T>
	{
	public:
		virtual void Handle(const std::shared_ptr<T>& unit, const ::google::protobuf::Message* message) override
		{
			Run(session, static<T*>(message));
		}

		virtual void Run(const std::shared_ptr<T>& unit, const Request& message) = 0;

		virtual const Type GetRequestType() { return typeof(Request); }
		virtual const Type GetResponseType() { return typeof(nullptr); }
	};


}
