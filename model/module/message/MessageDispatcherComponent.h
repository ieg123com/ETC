#pragma once
#include "etc/etc.h"
#include "module/other/AppType.h"
#include "module/other/MessageType.h"
#include "OpcodeTypeComponent.h"

namespace Model
{
	class IMessage;
	class Session;

	// 消息调度组件
	class MessageDispatcherComponent:
		public Component
	{
		// 消息状态
		struct stMessageState
		{
			
			int32_t		app_type;
			// 消息类型
			EMessageType	msg_type;
			// 回调
			std::shared_ptr<IMessage> call_back;
			stMessageState() {
				app_type = EAppType::None;
				msg_type = EMessageType::Message;
			}

			void clear() {
				app_type = EAppType::None;
				msg_type = EMessageType::Message;
				call_back.reset();
			}
		};

		// 消息类型
		std::vector<stMessageState>	m_messages;

	public:

		static MessageDispatcherComponent* Instance;



		void Awake();

		void Clear();

		template<typename T>
		void RegisterMessage(const uint16_t msg_id, const EMessageType msg_type){
			OpcodeTypeComponent::Instance->RegisterMessage<T>(msg_id);
			m_messages[msg_id].msg_type = msg_type;
		}

		inline stMessageState& GetMessage(const uint16_t msg_id) {
			return m_messages[msg_id];
		}
	};
}