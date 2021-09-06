#pragma once
#include "etc/etc.h"

namespace Model
{
	class Session;

	// 外网消息调度记录组件
	// 用来记录消息调用的接口实例，接口所用的appType
	class MessageDispatcherComponent:
		public Component
	{

		// 消息类型
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