#include "TChannel.h"
#include "log/log.h"
#include "module/memory/Loop.h"
#include "wepoll/AWEpoll.h"
#include "PacketParser.h"
#include "TService.h"

namespace Model
{
	TChannel::TChannel():
		AChannel(0)
	{
		__Service = nullptr;
		__WEpoll = nullptr;
		SessionId = 0;
		__RecvBuffer = Loop<CircularBuffer>::Instance().Fetch();
		__SendBuffer = Loop<CircularBuffer>::Instance().Fetch();
		__SendCache = Loop<std::vector<char>>::Instance().Fetch();
		__Parser = new PacketParser(__RecvBuffer);
	}

	void TChannel::OnRead(const char* data, const size_t len)
	{
		__RecvBuffer->Write(data, len);
	}

	void TChannel::Send(const char* data, const size_t len)
	{
		if (IsDisposed())
		{
			LOG_WARN("�Ự���ͷţ��޷�������Ϣ!(ip = {},channel id = {})",
				RemoteAddress.ToString(), Id);
			return;
		}
		if (len > UINT16_MAX)
		{
			LOG_ERROR("���η��͵����ݴ�С��������!({} > {},ip = {},channel id = {})",
				len, UINT16_MAX,
				RemoteAddress.ToString(),
				Id);
			return;
		}
		uint16_t pack_size = len;
		__SendBuffer->Write(&pack_size, sizeof(pack_size));
		__SendBuffer->Write(data, len);
		__Service->__NeedStartSend.insert(Id);
	}

	void TChannel::__StartParse()
	{

	}

	void TChannel::__StartSend()
	{
		if (__SendBuffer->Length() == 0)return;	// û����Ҫ���͵�������
		if (__SendCache->empty())
		{
			__SendCache->resize(__SendBuffer->Length());
			__SendBuffer->Read((char*)__SendCache->data(), __SendCache->size());
		}

		if (__WEpoll->Send(SessionId, __SendCache->data(), __SendCache->size()))
		{
			uint16_t len, opcode = 0;
			memcpy(&len, __SendCache->data(), sizeof(len));
			memcpy(&opcode, __SendCache->data(), sizeof(opcode));
			__SendCache->clear();
		}
		else {
			// ����ʧ��
			LOG_ERROR("��������ʧ�� error:{}", __WEpoll->LastError);
		}
	}
}