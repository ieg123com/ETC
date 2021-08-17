#include "TChannel.h"
#include "Service.h"
#include "module/message/MessageDefines.h"


namespace Model
{
	void TChannel::OnRead(const char* data, const size_t len)
	{
		m_memory_split.AddData(data, len);
		if (!m_memory_split.Unpack())
		{
			return;
		}

		// ��Ϣ�������
		auto pack = m_memory_split.Data;
		stMessageHead head;
		memmove(&head, pack->data(), sizeof(head));
	}

	void TChannel::Send(const char* data, const size_t len)
	{

		__service->Send(SessionId, data, len);
	}

	void TChannel::Start()
	{

	}
}
