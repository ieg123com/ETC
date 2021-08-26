#include "TChannel.h"
#include "Service.h"
#include "module/message/MessageDefines.h"
#include "module/message/MessageDispatcherComponent.h"


namespace Model
{
	class TChannelAwakeSystem : AwakeSystem<TChannel, const std::shared_ptr<Service>&>
	{
	public:
		virtual void Awake(const std::shared_ptr<TChannel>& self, const std::shared_ptr<Service>& service) override
		{
			self->Awake(service);
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

		auto pack = std::make_shared<std::string>(std::move(m_memory_split.Data));
		auto session = GetHost<Session>();
		m_channel << std::move([session, pack] {
			MessageDispatcherComponent::Instance->Handle(session, pack->data(), pack->size());
			});
	}

	void TChannel::Send(const char* data, const size_t len)
	{
		uint16_t pack_size = len;
		m_send_buffer.Write(&pack_size, sizeof(pack_size));
		m_send_buffer.Write(data, len);

		if (m_send_data.empty())
		{
			m_send_data.resize(m_send_buffer.Length());
			m_send_buffer.Read((char*)m_send_data.data(), m_send_data.size());
		}

		m_channel << std::move([this] {
			this->StartSend();
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
				LOG_ERROR("接受数据时发生未知错误");
			}
		}
	}

	void TChannel::Awake(const std::shared_ptr<Service>& service)
	{
		IChannel::Awake(service);
	}

	void TChannel::Destroy()
	{
		Disconnect();
		m_channel << std::move([] {});
	}

	void TChannel::StartSend()
	{
		if (__service->Send(this->SessionId, this->m_send_data.data(), this->m_send_data.size()))
		{
			m_send_data.empty();
		}
		else {
			// 发送失败
			LOG_ERROR("发生数据失败 error:{}", __service->LastError);
		}
	}
}
