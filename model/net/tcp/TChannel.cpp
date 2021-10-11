#include "TChannel.h"
#include "log/log.h"
#include "module/memory/Loop.h"
#include "wepoll/AWEpoll.h"
#include "PacketParser.h"
#include "TService.h"

namespace Model
{
// 	TChannel::TChannel():
// 		AChannel(0)
// 	{
// 		__Service = nullptr;
// 		__WEpoll = nullptr;
// 		SessionId = 0;
// 		__RecvBuffer = Loop<CircularBuffer>::Instance().Fetch();
// 		__SendBuffer = Loop<CircularBuffer>::Instance().Fetch();
// 		__SendCache = Loop<std::vector<char>>::Instance().Fetch();
// 		__Parser = new PacketParser(__RecvBuffer);
// 	}
	TChannel::TChannel(const int64_t id, const std::shared_ptr<TService>& service, const std::shared_ptr<AWEpoll>& epoll)
	{
		ChannelType = EChannelType::Accept;
		Id = id;
		__Service = service;
		__WEpoll = epoll;
 		__RecvBuffer = Loop<CircularBuffer>::Instance().Fetch();
 		__SendBuffer = Loop<CircularBuffer>::Instance().Fetch();
		__SendCache = Loop<std::vector<char>>::Instance().Fetch();
 		__Parser = new PacketParser(__RecvBuffer);
		__IsSending = false;
		__IsConnected = true;
		SessionId = 0;
	}

	TChannel::TChannel(const int64_t id, const std::shared_ptr<TService>& service, const IPEndPoint& address)
	{
		ChannelType = EChannelType::Connect;
		Id = id;
		__Service = service;
		__RecvBuffer = Loop<CircularBuffer>::Instance().Fetch();
		__SendBuffer = Loop<CircularBuffer>::Instance().Fetch();
		__SendCache = Loop<std::vector<char>>::Instance().Fetch();
		__Parser = new PacketParser(__RecvBuffer);
		__WEpoll = std::make_shared<AWEpoll>();
		__WEpoll->OnComplete = std::bind(&TChannel::OnComplete, this, std::placeholders::_1);
		RemoteAddress = address;
		__IsSending = false;
		__IsConnected = false;
		SessionId = 0;
	}


	bool TChannel::IsDisposed() const
	{
		return (__WEpoll == nullptr);
	}

	void TChannel::Dispose()
	{
		if (ChannelType == EChannelType::Connect)
		{
			__WEpoll->Dispose();
		}
		__WEpoll.reset();
	}


	bool TChannel::Connect()
	{
		if (IsDisposed())return false;
		return __WEpoll->Connect(RemoteAddress);
	}


	void TChannel::Send(const char* data, const size_t len)
	{
		if (IsDisposed())
		{
			LOG_WARN("会话已释放，无法发送消息!(ip = {},channel id = {})",
				RemoteAddress.ToString(), Id);
			return;
		}
		if (len > UINT16_MAX)
		{
			LOG_ERROR("单次发送的数据大小超出限制!({} > {},ip = {},channel id = {})",
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

	void TChannel::OnComplete(AWEpoll& epoll)
	{
		epoll.OnConnect = std::bind(&TChannel::OnConnectComplete, this, std::placeholders::_1, std::placeholders::_2);
		epoll.OnRead = std::bind(&TChannel::OnReadComplete, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
		epoll.OnDisconnect = std::bind(&TChannel::OnDisconnectComplete, this, std::placeholders::_1, std::placeholders::_2);
	}

	void TChannel::OnConnectComplete(AWEpoll& epoll, const int32_t fd)
	{
		__IsConnected = true;

	}

	void TChannel::OnReadComplete(AWEpoll& epoll, const int32_t fd, const std::shared_ptr<std::vector<char>>& data)
	{
		__RecvBuffer->Write(data->data(), data->size());
		__StartParse();
	}

	void TChannel::OnDisconnectComplete(AWEpoll& epoll, const int32_t fd)
	{
		__IsConnected = false;
	}


	void TChannel::__StartParse()
	{
		while (__Parser->Unpack())
		{
			__Service->OnRead(Id, __Parser->Data);
		}
	}

	void TChannel::__StartSend()
	{
		if (__SendBuffer->Length() == 0)return;	// 没有需要发送的数据了
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
			// 发送失败
			LOG_ERROR("发送数据失败 error:{}", __WEpoll->LastError);
		}
	}
}