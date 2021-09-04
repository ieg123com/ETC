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

	class IMessageSystem :
		public ISupportTypeCreation
	{
	public:
		virtual const Type GetRequestType() const = 0;
		virtual const Type GetResponseType() const = 0;

		int32_t appType = 0;
	};


	class IMessageHandler :
		public IMessageSystem
	{
	public:
		virtual void Handle(const std::shared_ptr<Session>& session, const char* data,const size_t len) = 0;

	};


	template<typename Request>
	class MessageHandler :
		public IMessageHandler
	{
	public:
		virtual void Handle(const std::shared_ptr<Session>& session, const char* data, const size_t len) override
		{
			Request request;
			if (!request.ParseFromArray(data, len))
			{
				throw std::exception("��������ʧ�ܣ�");
			}
			Run(session, request);
		}

		virtual void Run(const std::shared_ptr<Session>& session, Request& message) = 0;

		virtual const Type GetRequestType() const override { return typeof(Request); }
		virtual const Type GetResponseType() const override { return typeof(IMessage); }
	};

}








