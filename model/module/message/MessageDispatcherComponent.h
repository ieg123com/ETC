#pragma once
#include "etc/etc.h"
#include "module/other/AppType.h"

namespace Model
{
	class IMessage;
	// 消息调度组件
	class MessageDispatcherComponent:
		public Component
	{
		// 消息状态
		struct stMessageState
		{
			// 消息类型
			int32_t	msg_type;
			// 回调
			std::shared_ptr<IMessage> call_back;
			stMessageState() {
				msg_type = (int32_t)EAppType::None;
			}
		};
	public:

		static MessageDispatcherComponent* Instance;


		std::unordered_map<Type, std::set<Type>>	__m_types;
		// 消息类型
		std::vector<stMessageState>	__m_message;

		void Awake();


		void Clear();






	};
}