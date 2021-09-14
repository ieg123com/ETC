#pragma once
#include "etc/etc.h"

namespace Model
{
	class SessionPlayerComponent :
		public Component
	{
	public:
		ID	ListId;
		ID	MapId;
		ID	ChatId;
		ID	SocialId;

		void SetId(const EAppType app_type, const ID id);
		ID GetId(const EAppType app_type);

		ID GetIdByOpcode(const uint16_t opcode);
	};
}