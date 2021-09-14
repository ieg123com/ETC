#include "Session.h"
#include "Service.h"
#include "module/message/MessageDefines.h"
#include "module/message/OpcodeTypeComponent.h"
#include "etc/etc.h"
#include "IChannel.h"
#include "other/string/bytes.h"


namespace Model
{

	class SessionAwakeSystem :public AwakeSystem<Session,const std::shared_ptr<Service>&>
	{
	public:
		virtual void Awake(const std::shared_ptr<Session>& self, const std::shared_ptr<Service>& service)override
		{
			self->Awake(service);
		}
	};
	REF(SessionAwakeSystem, ObjectSystem);

	class SessionDestroySystem :public DestroySystem<Session>
	{
	public:
		virtual void Destroy(const std::shared_ptr<Session>& self) override
		{
			self->Destroy();
		}
	};
	REF(SessionDestroySystem, ObjectSystem);


	void Session::Awake(const std::shared_ptr<Service>& service)
	{
		RpcId = 0;
		__service = service;
	}

	void Session::Destroy()
	{
		// Service
		if (__service)
		{
			if (__service->GetNetworkType() == NetworkType::Server)
			{
				// 服务类型为服务器
				__service->Close(SessionId);
				__service.reset();
			}
			else if (__service->GetNetworkType() == NetworkType::Client)
			{
				// 服务类型为客户端
				__service->Dispose();
				__service.reset();
			}
		}
		// IChannel
		if (__channel)
		{
			__channel->Dispose();
			__channel.reset();
		}
	}

	void Session::OnRead(const char* data, const size_t len)
	{
		if (__channel)
		{
			__channel->OnRead(data, len);
		}
	}

	void Session::Send(const char* data, const size_t len)
	{
		if (__channel)
		{
			__channel->Send(data, len);
		}
	}

	void Session::Send(const uint16_t opcode, const char* data, const size_t len)
	{
		m_data_sent.resize(sizeof(opcode) + len);
		memcpy(&m_data_sent[0], &opcode, sizeof(opcode));
		memcpy(&m_data_sent[sizeof(opcode)], data, len);
		Send(m_data_sent.data(), m_data_sent.size());
	}

	void Session::Send(const int64_t actor_id, const IMessage* message)
	{
		uint16_t opcode = message->GetOpcode();
		int bytes_size = message->ByteSize();
		m_data_sent.resize(bytes_size + sizeof(opcode) + sizeof(actor_id));
		memcpy(&m_data_sent[0], &opcode, sizeof(opcode));
		memcpy(&m_data_sent[sizeof(opcode)], &actor_id, sizeof(actor_id));
		message->SerializePartialToArray(&m_data_sent[sizeof(opcode) + sizeof(actor_id)], bytes_size);
		Send(m_data_sent.data(), m_data_sent.size());
	}

	void Session::Send(const IMessage* message)
	{
		uint16_t opcode = message->GetOpcode();
		int bytes_size = message->ByteSize();
		m_data_sent.resize(bytes_size + sizeof(opcode));
		memcpy(&m_data_sent[0], &opcode, sizeof(opcode));
		message->SerializePartialToArray(&m_data_sent[sizeof(opcode)], bytes_size);
		Send(m_data_sent.data(), m_data_sent.size());
	}

	void Session::Reply(const IMessage* message)
	{
		switch (message->GetMessageType())
		{
		case EMessageType::IResponse:
			Send(message);
			break;
		case EMessageType::IActorResponse:
		case EMessageType::IActorLocationResponse:
			Send(0, message);
			break;
		default:
			LOG_ERROR("有一条要回复的消息出错，原因是因为发生的消息类型不对 Type = {},MessageType = {}",
				message->GetType().full_name(), ToString(message->GetMessageType()));
			break;
		}
	}




}