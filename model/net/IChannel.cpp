#include "IChannel.h"
#include "Service.h"
#include "Session.h"

namespace Model
{

	void IChannel::Awake()
	{
		__session = GetHost<Session>();
		__session->__channel = Get<IChannel>();
	}

	void IChannel::Destroy()
	{
		__session.reset();
	}
}