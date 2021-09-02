#pragma once
#include "IMessage.h"



namespace Model
{
	class Unit;

	class IMActorHandler :
		public IMessage 
	{
	public:
		virtual void Handle(const std::shared_ptr<Session>& session, const char* data, const size_t len) = 0;

		virtual FMRequestParse GetRequestParse()const = 0;
	};

	template<typename T,typename Request>
	class MActorHandler :
		public IMActorHandler
	{
	public:
		virtual void Handle(const std::shared_ptr<Session>& session, const char* data, const size_t len) override
		{
			Request request;
			if (!request.ParseFromArray(data, len))
			{
				throw std::exception("��������ʧ�ܣ�");
			}
			Run(std::dynamic_pointer_cast<T>(unit), request);
		}

		virtual void Run(const std::shared_ptr<T>& unit, Request& message) = 0;

		virtual const Type GetRequestType() const override { return typeof(Request); }
		virtual const Type GetResponseType() const override { return typeof(IMessage); }
		virtual FMRequestParse GetRequestParse()const override {
			return MRequestParse<Request>()();
		}
	};


}
