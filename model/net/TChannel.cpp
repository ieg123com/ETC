#include "TChannel.h"
#include "Service.h"
#include "module/message/MessageDefines.h"


namespace Model
{
	class TChannelAwakeSystem : AwakeSystem<TChannel, const std::shared_ptr<Service>&>
	{
	public:
		virtual void Awake(const std::shared_ptr<TChannel>& self, const std::shared_ptr<Service>& service) override
		{
			self->__service = service;
		}
	};
	REF(TChannelAwakeSystem, ObjectSystem);

	class TChannelDestroySystem : DestroySystem<TChannel>
	{
	public:
		virtual void Destroy(const std::shared_ptr<TChannel>& self) override
		{
			self->Disconnect();
		}
	};
	REF(TChannelDestroySystem, ObjectSystem);

	void TChannel::OnRead(const char* data, const size_t len)
	{
		m_memory_split.AddData(data, len);
		if (!m_memory_split.Unpack())
		{
			return;
		}

		// 消息解析完成
		auto pack = m_memory_split.Data;
		stMessageHead head;
		memmove(&head, pack.data(), sizeof(head));
	}

	void TChannel::Send(const char* data, const size_t len)
	{
		uint16_t pack_size = len;
		m_send_buffer.Write(&pack_size, sizeof(pack_size));
		m_send_buffer.Write(data, len);

		__service->Send(SessionId, m_send_data.data(), m_send_data.size());
	}

	void TChannel::Start()
	{
		while (!m_channel.empty() || )
		{

		}
	}
}
