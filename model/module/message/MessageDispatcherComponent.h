#pragma once
#include "etc/etc.h"
#include "module/other/AppType.h"
#include "module/other/MessageType.h"
#include "OpcodeTypeComponent.h"

namespace Model
{
	class IMessage;
	class Session;

	// ��Ϣ�������
	class MessageDispatcherComponent:
		public Component
	{
		// ��Ϣ״̬
		struct stMessageState
		{
			
			int32_t		app_type;
			// ��Ϣ����
			EMessageType	msg_type;
			// �ص�
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

		// ��Ϣ����
		std::vector<stMessageState>	m_messages;

	public:

		static MessageDispatcherComponent* Instance;



		void Awake();

		void Clear();

		template<typename T>
		void RegisterMessage(const uint16_t opcode){
			OpcodeTypeComponent::Instance->RegisterMessage<T>(opcode);
		}

		inline stMessageState& GetMessage(const uint16_t opcode) {
			return m_messages[opcode];
		}
	};
}