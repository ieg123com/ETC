#include "TChannel.h"
#include "module/memory/Loop.h"
#include "PacketParser.h"

namespace Model
{
	TChannel::TChannel():
		AChannel(0)
	{
		__Service = nullptr;
		__WEpoll = nullptr;
		__RecvBuffer = Loop<CircularBuffer>::Instance().Fetch();
		__SendBuffer = Loop<CircularBuffer>::Instance().Fetch();
		__Parser = new PacketParser(__RecvBuffer);
	}

}