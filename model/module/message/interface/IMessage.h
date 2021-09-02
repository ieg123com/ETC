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
	template<typename T>
	struct MRequestParse
	{
		FMRequestParse operator()()const noexcept {
			return [](stIMRequest& strequest, const char* data, const uint16_t len)->std::shared_ptr<PBMessage> {
				auto mrequest = std::make_shared<T>();
				if (!mrequest->ParseFromArray(data, len))
				{
					return nullptr;
				}
				strequest.RpcId = mrequest->rpcid();
				return mrequest;
			};
		}
	};


	template<typename T>
	struct MResponseParse
	{
		FMResponseParse operator()()const noexcept {
			return [](stIMResponse& stresponse, const char* data, const uint16_t len)->std::shared_ptr<PBMessage> {
				auto mresponse = std::make_shared<T>();
				if (!mresponse->ParseFromArray(data, len))
				{
					return nullptr;
				}
				stresponse.RpcId = mresponse->rpcid();
				stresponse.Error = mresponse->error();
				stresponse.Message = mresponse->message();
				return mresponse;
			};
		}
	};

	template<typename T>
	struct MResetResponse
	{
		FMResetResponse operator()()const noexcept {
			return [](PBMessage* response, const stIMResponse& stresponse)->bool {
				auto mresponse = dynamic_cast<T>(response);
				if (!mresponse)return false;
				mresponse->set_rpcid(stresponse.RpcId);
				mresponse->set_error(stresponse.Error);
				mresponse->set_message(stresponse.Message);
				return true;
			};
		}
	};



	class IMessage :
		public ISupportTypeCreation
	{
	public:
		virtual const Type GetRequestType() const = 0;
		virtual const Type GetResponseType() const = 0;

		int32_t appType = 0;
	};


	class IMessageHandler :
		public IMessage
	{
	public:
		virtual void Handle(const std::shared_ptr<Session>& session, const char* data,const size_t len) = 0;

		virtual FMRequestParse GetRequestParse()const = 0;
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
				throw std::exception("½âÎöÊý¾ÝÊ§°Ü£¡");
			}
			Run(session, request);
		}

		virtual void Run(const std::shared_ptr<Session>& session, Request& message) = 0;

		virtual const Type GetRequestType() const override { return typeof(Request); }
		virtual const Type GetResponseType() const override { return typeof(IMessage); }
		virtual FMRequestParse GetRequestParse()const override {
			return MRequestParse<Request>()();
		}
	};

}








