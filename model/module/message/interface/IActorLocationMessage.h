#pragma once
#include "IMessage.h"


namespace Model
{

	class IMActorLocationHandler :	
		public IMessage
	{
	public:
		virtual void Handle(const std::shared_ptr<Session>& session, const char* data, const size_t len) = 0;

	};


	template<typename T, typename Request>
	class MActorLocationHandler :
		public IMActorLocationHandler
	{
	public:
		virtual void Handle(const std::shared_ptr<Session>& session, const char* data, const size_t len) override
		{
			Request request;
			if (!request.ParseFromArray(data, len))
			{
				throw std::exception("½âÎöÊý¾ÝÊ§°Ü£¡");
			}
			Run(std::dynamic_pointer_cast<T>(unit), request);
		}

		virtual void Run(const std::shared_ptr<T>& unit, Request& request) = 0;

		virtual const Type GetRequestType() const override { return typeof(Request); }
		virtual const Type GetResponseType() const override { return typeof(nullptr); }
	};

}