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

	void Session::__Reply(const Type& tp, const ::google::protobuf::Message* message)
	{
		uint16_t opcode = 0;
		try {
			opcode = OpcodeTypeComponent::Instance->GetTypeOpcodeTry(tp);
		}
		catch (std::exception& e)
		{
			LOG_ERROR("回复消息失败:{} {}", tp.class_name(), e.what());
			return;
		}
		int bytes_size = message->ByteSize();
		m_data_sent.resize(bytes_size + sizeof(opcode));
		memcpy(&m_data_sent[0], &opcode, sizeof(opcode));
		message->SerializePartialToArray(&m_data_sent[2], bytes_size);
		Send(m_data_sent.data(), m_data_sent.size());
	}
}