#pragma once
#include <memory>
#include "interface/ISupportTypeCreation.h"
#include "google/protobuf/message.h"
#include "type/type.h"
#include "type/type_factory.h"
#include "etc/kernel/Entity.h"
#include "net/Session.h"
#include "module/message/MessageDefines.h"



namespace Model
{

	class IMSystemHandler :
		public ISupportTypeCreation
	{
	public:
		virtual const Type GetRequestType() const = 0;
		virtual const Type GetResponseType() const = 0;

		int32_t appType = 0;
	};


	class IMessageHandler :
		public IMSystemHandler
	{
	public:
		virtual void Handle(const std::shared_ptr<Session>& session, IMessage* message) = 0;

	};


	template<typename Request>
	class MessageHandler :
		public IMessageHandler
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

}








