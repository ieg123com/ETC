#include "model/module/message/OpcodeTypeComponent.h"
#include "model/module/other/SystemEventType.h"
#include "model/module/message.h"

class OpcodeTypeComponentAwakeSystem :public AwakeSystem<OpcodeTypeComponent>
{
public:
	virtual void Awake(const std::shared_ptr<OpcodeTypeComponent>& self) override
	{
		self->Awake();
	}
};
REF(OpcodeTypeComponentAwakeSystem, ObjectSystem);

class OpcodeTypeComponentLoadSystem :public LoadSystem<OpcodeTypeComponent>
{
public:
	virtual void Load(const std::shared_ptr<OpcodeTypeComponent>& self)override
	{
		OpcodeTypeComponent::Instance = self.get();

		self->Load();

		{
			// 注册消息
			auto proto_message = Game::Event().GetAssemblysType<ProtoMessage>();
			for (auto& item : proto_message)
			{
				auto message = TypeFactory::CreateInstance<IMessage>(item.second->GetObjectType());

				self->__RegisterMessage(message->GetType(), message->GetOpcode(),message->GetMessageType());

				if (message->GetMessageType() == EMessageType::IActorMessage ||
					message->GetMessageType() == EMessageType::IActorLocationMessage)
				{
					// 为 ActorMessage 绑定默认回复消息
					self->__BindRpcMessage(message->GetType(), typeof(ActorResponse));
				}
			}

			// 绑定Rpc消息，通过消息内部反射
			auto mproto_message = Game::Event().GetAssemblysType<ProtoResponseMessage>();
			for (auto& item : mproto_message)
			{
				auto attr_type = item.second->GetObjectType();
				if (auto attr = std::dynamic_pointer_cast<ProtoResponseMessage>(item.second))
				{
					self->__BindRpcMessage(attr->GetObjectType(), attr->ResponseMessageType);
				}
			}

			// 绑定Rpc消息，通过消息处理对象
			auto message_handler = Game::Event().GetAssemblysType<Message>();
			for (auto& item : message_handler)
			{
				Type handler_type = item.second->GetObjectType();
				Type type_req, type_rpo;
				auto handler = TypeFactory::CreateInstance<IMSystemHandler>(handler_type);
				type_req = handler->GetRequestType();
				type_rpo = handler->GetResponseType();
				self->__BindRpcMessage(type_req, type_rpo);
// 				if (auto instance = std::dynamic_pointer_cast<IMHandler>(handler))
// 				{
// 					// 普通外网通信 回复类型绑定
// 					
// 				}
// 				else if (auto instance = std::dynamic_pointer_cast<IMActorHandler>(handler))
// 				{
// 					// Actor 回复类型绑定
// 					type_req = instance->GetRequestType();
// 					type_rpo = instance->GetResponseType();
// 					self->__BindRpcMessage(type_req, type_rpo);
// 				}
			}

		}

	}
};
REF(OpcodeTypeComponentLoadSystem, ObjectSystem);

class OpcodeTypeComponentDestroySystem :public DestroySystem<OpcodeTypeComponent>
{
public:
	virtual void Destroy(const std::shared_ptr<OpcodeTypeComponent>& self)override
	{
		self->Destroy();
	}
};
REF(OpcodeTypeComponentDestroySystem, ObjectSystem);