#pragma once
#include "etc/etc.h"

class IMHandler;
class IMessage;

namespace Model
{
	class Session;


	// 外网消息调度记录组件
	// 用来记录消息调用的接口实例，接口所用的appType
	class MessageDispatcherComponent:
		public Component
	{

		// 消息类型
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