#include "TChannel.h"
#include "Service.h"
#include "Session.h"
#include "module/message/MessageDefines.h"
#include "module/message/MessageDispatcherComponent.h"
#include "module/message/IMessageDispatcher.h"
#include "etc/etc_config.h"
#include "net/NetworkComponent.h"
#include "other/string/bytes.h"



namespace Model
{

	TChannel::TChannel():
		m_channel(NETWORK_CHANNEL_CAPACITY)
	{

	}

	void TChannel::OnRead(const char* data, const size_t len)
	{
		m_memory_split.Write(data, len);
		while (true)
		{
			if (!m_memory_split.Unpack())
			{
				break;
			}
			// ��Ϣ�������
			auto pack = std::make_shared<std::string>(std::move(m_memory_split.Data));
			auto session = GetHost<Session>();
			session->__networkcomponent->__MessageDispatcher->Dispatch(session, pack->data(), pack->size());
// 			if (!m_channel.TryPush(std::move([session, pack] {
// 				session->__networkcomponent->__MessageDispatcher->Dispatch(session, pack->data(), pack->size());
// 				})))
// 			{
// 				// ���������������,��ǰ�Ự�����˶���
// 				LOG_WARN("��ȡ����ʱ���֣��������������������ǰ�Ự�����˶�����(ip = {},fd = {})",
// 					session->Address.ToString(), session->SessionId);
// 				// �Ͽ������������ĻỰ
// 				session->Dispose();
// 			}
		}
	}

	void TChannel::Send(const char* data, const size_t len)
	{
		if (IsDisposed())
		{
			LOG_WARN("�Ự���ͷţ��޷�������Ϣ!(ip = {},fd = {})",
				m_session->Address.ToString(), m_session->SessionId);
			return;
		}
		if (len > UINT16_MAX)
		{
			LOG_ERROR("���η��͵����ݴ�С��������!({} > {},ip = {},fd = {})",
				len, UINT16_MAX,
				m_session->Address.ToString(),
				m_session->SessionId);
			return;
		}
		uint16_t pack_size = len;
		m_send_buffer.Write(&pack_size, sizeof(pack_size));
		m_send_buffer.Write(data, len);
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
				LOG_ERROR("��������ʱ��������:{}", e.what());
			}
			catch (...)
			{
				LOG_ERROR("��������ʱ����δ֪����");
			}
		}

		m_session.reset();
	}

	void TChannel::Awake()
	{
		IChannel::Awake();
		m_session = __session;
	}

	void TChannel::LateUpdate()
	{
		__StartSend();
	}

	void TChannel::Destroy()
	{
		m_channel.TryPush(std::move([] {}));
		IChannel::Destroy();
	}

	void TChannel::__StartSend()
	{
		if (m_send_buffer.Length() == 0)return;	// û����Ҫ���͵�������
		if (m_send_data.empty()) 
		{
			m_send_data.resize(m_send_buffer.Length());
			m_send_buffer.Read((char*)m_send_data.data(), m_send_data.size());
		}
		LOG_INFO("__StartSend");
		auto service = m_session->__service;

		if (service->Send(m_session->SessionId, m_send_data.data(), m_send_data.size()))
		{
			uint16_t len, opcode = 0;
			memcpy(&len, &m_send_data[0], sizeof(len));
			memcpy(&opcode, &m_send_data[2], sizeof(opcode));
			m_send_data.clear();
		}
		else {
			// ����ʧ��
			LOG_ERROR("��������ʧ�� error:{}", service->LastError);
		}
		
	}
}
