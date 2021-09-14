#include "SessionPlayerComponent.h"
#include "module/message/MessageDispatcherComponent.h"


namespace Model
{


	void SessionPlayerComponent::SetId(const EAppType app_type, const ID id)
	{
		switch (app_type)
		{
		case EAppType::List:	ListId = id; break;
		case EAppType::Map:		MapId = id; break;
		case EAppType::Chat:	ChatId = id; break;
		case EAppType::Social:	SocialId = id; break;
		default:
			break;
		}
	}

	ID SessionPlayerComponent::GetId(const EAppType app_type)
	{
		switch (app_type)
		{
		case EAppType::List:	return ListId; break;
		case EAppType::Map:		return MapId; break;
		case EAppType::Chat:	return ChatId; break;
		case EAppType::Social:	return SocialId; break;
		default:
			break;
		}
		return 0;
	}

	ID SessionPlayerComponent::GetIdByOpcode(const uint16_t opcode)
	{
		return GetId(MessageDispatcherComponent::Instance->MessageAppType[opcode]);
	}

}