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
			go[self]{
				self->Start();
			};
		}
	};
	REF(TChannelAwakeSystem, ObjectSystem);

	class TChannelDestroySystem : DestroySystem<TChannel>
	{
	public:
		virtual void Destroy(const std::shared_ptr<TChannel>& self) override
		{
			self->Destroy();
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

		m_send_data.resize(m_send_buffer.Length());

		m_channel << std::move([this] {
			this->__service->Send(this->SessionId, this->m_send_data.data(), this->m_send_data.size());
			this->m_send_data.empty();
		});
	}

	void TChannel::Start()
	{
		std::function<void()> func;
		while (!m_channel.empty() || !IsDisposed())
		{
			m_channel >> std::move(func);
			try
			{
				func();
			}
			catch (std::exception& e)
			{
				LOG_ERROR("接受数据时发生错误:{}", e.what());
			}
			catch (...)
			{
				LOG_ERROR("未知错误");
			}
		}
	}

	void TChannel::Destroy()
	{
		Disconnect();
		m_channel << std::move([] {});
	}

}
