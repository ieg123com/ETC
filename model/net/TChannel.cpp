#include "TChannel.h"
#include "Service.h"
#include "Session.h"
#include "module/message/MessageDefines.h"
#include "module/message/MessageDispatcherComponent.h"
#include "module/message/IMessageDispatcher.h"
#include "etc/etc_config.h"
#include "net/NetworkComponent.h"



namespace Model
{
	class TChannelAwakeSystem : AwakeSystem<TChannel>
	{
	public:
		virtual void Awake(const std::shared_ptr<TChannel>& self) override
		{
			self->Awake();
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

	TChannel::TChannel():
		m_channel(NETWORK_CHANNEL_CAPACITY)
	{

	}

	void TChannel::OnRead(const char* data, const size_t len)
	{
		m_memory_split.Write(data, len);
		if (!m_memory_split.Unpack())
		{
			return;
		}
		// 消息解析完成
		auto pack = std::make_shared<std::string>(std::move(m_memory_split.Data));
		auto session = GetHost<Session>();
		if (!m_channel.TryPush(std::move([session, pack] {
			session->__networkcomponent->__MessageDispatcher->Dispatch(session, pack->data(), pack->size());
			})))
		{
			// 缓存队列容量已满,当前会话发生了堵塞
			LOG_WARN("缓存队列容量已满,当前会话发生了堵塞。(ip = {},fd = {})",
				session->Address.ToString(), session->SessionId);
			// 断开这个出现问题的会话
			session->Dispose();
		}

	}

	void TChannel::Send(const char* data, const size_t len)
	{
		if (IsDisposed())
		{
			LOG_WARN("会话已释放，无法发送消息!(ip = {},fd = {})",
				m_session->Address.ToString(), m_session->SessionId);
			return;
		}
		if (len > UINT16_MAX)
		{
			LOG_ERROR("单次发送的数据大小超出限制!({} > {},ip = {},fd = {})",
				len, UINT16_MAX,
				m_session->Address.ToString(),
				m_session->SessionId);
			return;
		}
		uint16_t pack_size = len;
		m_send_buffer.Write(&pack_size, sizeof(pack_size));
		m_send_buffer.Write(data, len);

		if (m_send_data.empty())
		{
			m_send_data.resize(m_send_buffer.Length());
			m_send_buffer.Read((char*)m_send_data.data(), m_send_data.size());
		}
		if (!m_channel.TryPush(std::move([this] {
			this->StartSend();
			})))
		{

		}

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

		m_session.reset();
	}

	void TChannel::Awake()
	{
		IChannel::Awake();
		m_session = __session;
	}

	void TChannel::Destroy()
	{
		m_channel.TryPush(std::move([] {}));
		IChannel::Destroy();
	}

	void TChannel::StartSend()
	{
		if (auto service = m_session->__service)
		{
			if (service->Send(m_session->SessionId, this->m_send_data.data(), this->m_send_data.size()))
			{
				m_send_data.empty();
			}
			else {
				// 发送失败
				LOG_ERROR("发送数据失败 error:{}", service->LastError);
			}
		}
		
	}
}
