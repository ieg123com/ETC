#pragma once
#include <memory>
#include "interface/ISupportTypeCreation.h"
#include "google/protobuf/message.h"
#include "type/type.h"
#include "etc/kernel/Entity.h"
#include "net/Session.h"


namespace Model
{
	class Session;

	class IMessage :
		public ISupportTypeCreation
	{
	public:
		virtual const Type GetRequestType() = 0;
		virtual const Type GetResponseType() = 0;
	};


	class IMessageSystem :
		public IMessage
	{
	public:
		virtual void Handle(const std::shared_ptr<Session>& session, ::google::protobuf::Message* message) = 0;
		
	};


	template<typename Request>
	class MessageSystem :
		public IMessageSystem
	{
	public:
		virtual void Handle(const std::shared_ptr<Session>& session, ::google::protobuf::Message* message) override
		{
			Run(session, static<Request*>(message));
		}

		virtual void Run(const std::shared_ptr<Session>& session, const Request& message) = 0;

		virtual const Type GetRequestType() { return typeof(Request); }
		virtual const Type GetResponseType() { return typeof(nullptr); }
	};

}








