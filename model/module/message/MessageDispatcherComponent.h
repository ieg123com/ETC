#pragma once
#include "etc/etc.h"
#include "module/other/AppType.h"

namespace Model
{
	class IMessage;
	// ��Ϣ�������
	class MessageDispatcherComponent:
		public Component
	{
		// ��Ϣ״̬
		struct stMessageState
		{
			// ��Ϣ����
			int32_t	msg_type;
			// �ص�
			std::shared_ptr<IMessage> call_back;
			stMessageState() {
				msg_type = (int32_t)EAppType::None;
			}
		};
	public:

		static MessageDispatcherComponent* Instance;

		std::unordered_map<Type, uint16_t> __m_message_id;
		// ��Ϣ����
		std::vector<stMessageState>	__m_message;

		void Awake();

		void Clear();

		template<typename T>
		void RegisterMessage(const uint16_t msg_id, const int32_t msg_type){

			static_assert(std::is_base_of(::google::protobuf::Message, T)::value,
				"The registered message must inherit '::google::protobuf::Message'");
			__m_message_id[typeof(msg_id)] = msg_id;
			__m_message[msg_id].msg_type = msg_type;
		}





	};
}