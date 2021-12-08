#include "NetInnerComponent.h"
#include "IMessageDispatcher.h"
#include "net/Session.h"
#include "net/AService.h"



namespace Model
{
	NetInnerComponent* NetInnerComponent::Instance = nullptr;

	void NetInnerComponent::Destroy()
	{
		__Service->Dispose();

	}

	std::shared_ptr<Session> NetInnerComponent::GetOrCreate(const int64_t channel_id, const IPEndPoint& address)
	{
		if (auto session = GetChild<Session>(channel_id))
		{
			return session;
		}
		if (__Service->Create(channel_id, address))
		{
			// 连接成功
			// 创建新Session,用来记录连接
			auto session = ObjectFactory::CreateWithHostAndId<Session, const std::shared_ptr<AService>&>(Self(), channel_id, __Service);
			session->RemoteAddress = address;
			return session;
		}
		return nullptr;
	}

	void NetInnerComponent::__OnAccept(const int64_t channel_id, const IPEndPoint& address)
	{
		auto session = ObjectFactory::CreateWithHostAndId<Session,const std::shared_ptr<AService>&>(Self(), channel_id, __Service);
		session->RemoteAddress = address;

	}

	void NetInnerComponent::__OnRead(const int64_t channel_id, std::shared_ptr<std::vector<char>> data)
	{
		if (auto session = GetChild<Session>(channel_id))
		{
			__MessageDispatcher->Dispatch(session, data->data(), data->size());
		}
	}

	void NetInnerComponent::__OnDisconnect(const int64_t channel_id)
	{
		if (auto session = GetChild<Session>(channel_id))
		{
			session->Dispose();
		}
	}


}
