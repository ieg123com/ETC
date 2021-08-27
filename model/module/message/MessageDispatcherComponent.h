#pragma once
#include "etc/etc.h"
#include "module/other/AppType.h"
#include "module/other/MessageType.h"

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

		struct stMessageTypeState
		{
			uint16_t	msg_id;
			int32_t		app_type;
			stMessageTypeState() {
				msg_id = 0;
				app_type = EAppType::None;
			}
			stMessageTypeState(const uint16_t id) {
				msg_id = id;
				app_type = EAppType::None;
			}
		};
	public:

		static MessageDispatcherComponent* Instance;

		std::unordered_map<Type, stMessageTypeState> __m_message_type;
		// ��Ϣ����
		std::vector<stMessageState>	__m_message;

		void Awake();

		void Clear();

		template<typename T>
		void RegisterMessage(const uint16_t msg_id, const EMessageType msg_type){

			//static_assert(std::is_base_of(::google::protobuf::Message, T)::value,
			//	"The registered message must inherit '::google::protobuf::Message'");
			if (!__m_message_type.insert(std::make_pair(typeof(T), msg_id)).second)
				throw std::exception(std::format("����Ϣ�ַ��У�ͬһ��Ϣ��ע���˶�� %s:%u",typeof(T).class_name(),msg_id).c_str());
			
			__m_message[msg_id].msg_type = msg_type;
		}

		void Handle(const std::shared_ptr<Session>& session, const char* data, const size_t len);



	};
}