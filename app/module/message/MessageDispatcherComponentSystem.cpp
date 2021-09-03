#include "model/module/message/MessageDispatcherComponent.h"
#include "model/module/other/SystemEventType.h"

using namespace Model;


namespace Hotfix
{

	class MessageDispatcherComponentAwakeSystem :public AwakeSystem<MessageDispatcherComponent>
	{
	public:
		virtual void Awake(const std::shared_ptr<MessageDispatcherComponent>& self) override
		{
			LOG_INFO("MessageDispatcherComponent Awake");
			self->Awake();
		}
	};
	REF(MessageDispatcherComponentAwakeSystem, ObjectSystem);

	class MessageDispatcherComponentLoadSystem :public LoadSystem<MessageDispatcherComponent>
	{
	public:
		virtual void Load(const std::shared_ptr<MessageDispatcherComponent>& self)override
		{
			LOG_INFO("MessageDispatcherComponent Load");
			MessageDispatcherComponent::Instance = self.get();
			self->Clear();
			Game::Event().Run<const std::shared_ptr<MessageDispatcherComponent>&>(ESystemEventType::StartRegMessage, self);
			
			{
				// TODO:  给指定消息id设置回调函数
				auto& message_system = Game::Event().__message_system;
				for (auto& item : message_system)
				{
					// 请求消息
					try
					{
						uint16_t opcode_req = OpcodeTypeComponent::Instance->GetTypeOpcodeTry(item->GetRequestType());
						self->GetMessage(opcode_req).app_type = item->appType;
						self->GetMessage(opcode_req).call_back = item;

						if (auto message_handler = std::dynamic_pointer_cast<IMessageHandler>(item))
						{
							self->GetMessage(opcode_req).msg_type = EMessageType::Message;
						}
						else if (auto mrpc_handler = std::dynamic_pointer_cast<IMRpcHandler>(item))
						{
							uint16_t opcode_rpo = OpcodeTypeComponent::Instance->GetTypeOpcodeTry(mrpc_handler->GetResponseType());
							self->GetMessage(opcode_req).msg_type = EMessageType::Request;
							self->GetMessage(opcode_rpo).msg_type = EMessageType::Response;
						}
						else if (auto mactor_handler = std::dynamic_pointer_cast<IMActorHandler>(item))
						{
							uint16_t opcode_rpo = OpcodeTypeComponent::Instance->GetTypeOpcodeTry(mactor_handler->GetRequestType());
							self->GetMessage(opcode_req).msg_type = EMessageType::ActorMessage;
						}
						else if (auto mactor_rpc_handler = std::dynamic_pointer_cast<IMActorRpcHandler>(item))
						{
							uint16_t opcode_rpo = OpcodeTypeComponent::Instance->GetTypeOpcodeTry(mactor_rpc_handler->GetResponseType());
							self->GetMessage(opcode_req).msg_type = EMessageType::ActorRequest;
							self->GetMessage(opcode_rpo).msg_type = EMessageType::ActorResponse;
						}
						else if (auto mactor_location_handler = std::dynamic_pointer_cast<IMActorLocationHandler>(item))
						{
							uint16_t opcode_rpo = OpcodeTypeComponent::Instance->GetTypeOpcodeTry(mactor_location_handler->GetRequestType());
							self->GetMessage(opcode_req).msg_type = EMessageType::ActorMessage;
						}
						else if (auto mactor_location_rpc_handler = std::dynamic_pointer_cast<IMActorLocationRpcHandler>(item))
						{
							uint16_t opcode_rpo = OpcodeTypeComponent::Instance->GetTypeOpcodeTry(mactor_location_rpc_handler->GetResponseType());
							self->GetMessage(opcode_req).msg_type = EMessageType::ActorLocationRequest;
							self->GetMessage(opcode_rpo).msg_type = EMessageType::ActorLocationResponse;
						}
					}
					catch (std::exception& e)
					{
						LOG_WARN("没有注册的消息类型 {} {} error:{}", item->GetRequestType().full_name(),item->GetResponseType().full_name(),e.what());
					}
				}
			}
		}
	};
	REF(MessageDispatcherComponentLoadSystem, ObjectSystem);

}


