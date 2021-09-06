#pragma once
#include "etc/etc.h"

namespace Model
{
	class Session;

	// ������Ϣ���ȼ�¼���
	// ������¼��Ϣ���õĽӿ�ʵ�����ӿ����õ�appType
	class MessageDispatcherComponent:
		public Component
	{

		// ��Ϣ����
		std::vector<std::shared_ptr<IMessageHandler>>	m_message_handler;
		std::vector<std::shared_ptr<IMRpcHandler>>		m_mrpc_handler;

	public:
		static MessageDispatcherComponent* Instance;

		void Awake();

		void Clear();

		void RegisterMessage(const uint16_t opcode, const std::shared_ptr<IMSystemHandler> handler);

		void MessageHandle(const std::shared_ptr<Session>& session, const uint16_t opcode, const std::shared_ptr<IMessage>& message);
		void MRpcHandle(const std::shared_ptr<Session>& session, const uint16_t opcode, const std::shared_ptr<IRequest>& request);





	};



}