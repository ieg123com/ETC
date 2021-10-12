#include "NetOuterComponent.h"
#include "IMessageDispatcher.h"
#include "net/AService.h"
#include "net/Session.h"



namespace Model
{
	void NetOuterComponent::Destroy()
	{
		__Service->Dispose();

	}

	void NetOuterComponent::__OnAccept(const int64_t channel_id, const IPEndPoint& address)
	{
		auto session = ObjectFactory::CreateWithHostAndId<Session, std::shared_ptr<AService>>(Self(), channel_id, __Service);
		session->RemoteAddress = address;

	}

	void NetOuterComponent::__OnRead(const int64_t channel_id, std::shared_ptr<std::vector<char>> data)
	{
		if (auto session = GetChild<Session>(channel_id))
		{
			__MessageDispatcher->Dispatch(session, data->data(), data->size());
		}
	}

	void NetOuterComponent::__OnDisconnect(const int64_t channel_id)
	{
		if (auto session = GetChild<Session>(channel_id))
		{
			session->Dispose();
		}
	}


}
