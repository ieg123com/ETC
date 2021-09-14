#pragma once
#include "etc/etc.h"

class IMHandler;
class IMessage;

namespace Model
{
	class Session;


	// ������Ϣ���ȼ�¼���
	// ������¼��Ϣ���õĽӿ�ʵ�����ӿ����õ�appType
	class MessageDispatcherComponent:
		public Component
	{

		// ��Ϣ����
		std::vector<std::shared_ptr<IMHandler>>	m_message_handler;
		

	public:
		static MessageDispatcherComponent* Instance;

		std::vector<EAppType>		MessageAppType;

		void Awake();

		void Clear();

		void RegisterMessage(const uint16_t opcode, const std::shared_ptr<IMHandler>& handler);

		void Handle(const std::shared_ptr<Session>& session, const uint16_t opcode, IMessage* message);




	};


}