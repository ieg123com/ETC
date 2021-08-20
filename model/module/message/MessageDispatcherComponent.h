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


		std::unordered_map<Type, std::set<Type>>	__m_types;
		// ��Ϣ����
		std::vector<stMessageState>	__m_message;

		void Awake();


		void Clear();






	};
}