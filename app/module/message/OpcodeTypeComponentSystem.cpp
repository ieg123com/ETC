#include "model/module/message/OpcodeTypeComponent.h"
#include "model/module/other/SystemEventType.h"


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
			// ע����Ϣ
			auto proto_message = Game::Event().GetAssemblysType<ProtoMessage>();
			for (auto& item : proto_message)
			{
				auto message = TypeFactory::CreateInstance<IMessage>(item.second->GetObjectType());

				self->__RegisterMessage(message->GetType(), message->GetOpcode(),message->GetMessageType());

				if (message->GetMessageType() == EMessageType::IActorMessage ||
					message->GetMessageType() == EMessageType::IActorLocationMessage)
				{
					// Ϊ ActorMessage ��Ĭ�ϻظ���Ϣ
					self->__BindRpcMessage(message->GetType(), typeof(ActorResponse));
				}
			}

			// ��Rpc��Ϣ��ͨ����Ϣ�ڲ�����
			auto mproto_message = Game::Event().GetAssemblysType<ProtoResponseMessage>();
			for (auto& item : mproto_message)
			{
				auto attr_type = item.second->GetObjectType();
				if (auto attr = std::dynamic_pointer_cast<ProtoResponseMessage>(item.second))
				{
					self->__BindRpcMessage(attr->GetObjectType(), attr->ResponseMessageType);
				}
			}

			// ��Rpc��Ϣ��ͨ����Ϣ�������
			auto message_handler = Game::Event().GetAssemblysType<Message>();
			for (auto& item : message_handler)
			{
				Type handler_type = item.second->GetObjectType();
				Type type_req, type_rpo;
				auto handler = TypeFactory::CreateInstance<IMSystemHandler>(handler_type);
				if (auto instance = std::dynamic_pointer_cast<IMRpcHandler>(handler))
				{
					type_req = instance->GetRequestType();
					type_rpo = instance->GetResponseType();
					self->__BindRpcMessage(type_req, type_rpo);
				}
				else if (auto instance = std::dynamic_pointer_cast<IMActorHandler>(handler))
				{
					// IMActorLocationHandler ͬ���ᴥ������Ϊ�̳е� IMActorHandler
					type_req = instance->GetRequestType();
					type_rpo = instance->GetResponseType();
					self->__BindRpcMessage(type_req, type_rpo);
				}
				else if (auto instance = std::dynamic_pointer_cast<IMActorRpcHandler>(handler))
				{
					// IMActorLocaitonRpcHandler ͬ���ᴥ������Ϊ�̳е� IMActorRpcHandler
					type_req = instance->GetRequestType();
					type_rpo = instance->GetResponseType();
					self->__BindRpcMessage(type_req, type_rpo);
				}
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