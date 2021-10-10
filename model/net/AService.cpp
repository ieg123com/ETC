#include "AService.h"

namespace Model
{
	void AService::OnRead(const int64_t channel_id, const std::shared_ptr<std::vector<char>>& data)
	{
		if (ReadCallback)ReadCallback(channel_id, data);
	}

	void AService::OnAccept(const int64_t channel_id, const IPEndPoint& address)
	{
		if (AcceptCallback)AcceptCallback(channel_id, address);
	}

	void AService::OnError(const int64_t channel_id, const int err)
	{
		if (ErrorCallback)ErrorCallback(channel_id, err);
	}
}