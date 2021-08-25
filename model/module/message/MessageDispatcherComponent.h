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
				msg_type = EAppType::None;
			}

			void clear() {
				msg_type = EAppType::None;
				call_back.reset();
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

			//static_assert(std::is_base_of(::google::protobuf::Message, T)::value,
			//	"The registered message must inherit '::google::protobuf::Message'");
			if (!__m_message_id.insert(std::make_pair(typeof(T), msg_id)).second)
				throw std::exception(std::format("����Ϣ�ַ��У�ͬһ��Ϣ��ע���˶�� %s:%u",typeof(T).class_name(),msg_id).c_str());
			
			__m_message[msg_id].msg_type = msg_type;
		}

		void Handle(const uint16_t msg_id, const char* data, const char* len);



	};
}