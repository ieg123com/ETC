#pragma once
#include "IMessage.h"


namespace Model
{
	class IRpcMessageSystem:
		public IMessage
	{
	public:

		virtual void Handle(const std::shared_ptr<Session>& session, const ::google::protobuf::Message* request, const ::google::protobuf::Message* response) = 0;


	};


	template<typename Request,typename Response>
	class RpcMessageSystem :
		public IRpcMessageSystem
	{
	public:
		virtual void Handle(const std::shared_ptr<Session>& session, const ::google::protobuf::Message* request, const ::google::protobuf::Message* response) override
		{
			Run(session, static_cast<Request*>(request), static_cast<Response*>(response));
		}

		virtual void Run(const std::shared_ptr<Session>& session, const Request& request, const Response& response) = 0;

		virtual const Type GetRequestType() { return typeof(Request); }
		virtual const Type GetResponseType() { return typeof(Response); }
	};


}
