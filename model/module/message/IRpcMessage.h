#pragma once
#include "IMessage.h"


namespace Model
{
	template<typename T>
	class IRpcMessageSystem:
		public IMessage
	{
	public:

		virtual void Handle(const std::shared_ptr<T>& session, const ::google::protobuf::Message* request, const ::google::protobuf::Message* response) = 0;


	};


	template<typename T,typename Request,typename Response>
	class RpcMessageSystem :
		public IRpcMessageSystem<T>
	{
	public:
		virtual void Handle(const std::shared_ptr<T>& session, const ::google::protobuf::Message* request, const ::google::protobuf::Message* response) override
		{
			Run(session, static_cast<Request*>(request), static_cast<Response*>(response));
		}

		virtual void Run(const std::shared_ptr<T>& session, const Request& request, const Response& response) = 0;

		virtual const Type GetRequestType() { return typeof(Request); }
		virtual const Type GetResponseType() { return typeof(Response); }
	};


}
