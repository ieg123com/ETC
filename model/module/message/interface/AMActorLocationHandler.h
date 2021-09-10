#pragma once
#include "IMActorHandler.h"
#include "model/proto/EtcMsg.pb.h"





template<typename T, typename Request>
class MActorLocationHandler :
	public IMActorHandler
{
public:
	static_assert(std::is_base_of<IActorLocationMessage, Request>::value,
		"The Request type in MActorLocationHandler needs needs to be inherited from 'IActorLocationMessage'");

	virtual void Handle(const std::shared_ptr<GEntity>& entity, IMessage* message, const FMPReply& reply) override
	{
		try 
		{
			Request* request = dynamic_cast<Request*>(message);
			if (request == nullptr)
			{
				throw std::exception(std::format("ת����Ϣ����ʧ��: %s => %s",
					message->GetType().full_name(),
					typeof(Request).full_name()
				).c_str());
			}
			ActorResponse response;

			auto unit = std::dynamic_pointer_cast<T>(entity);
			if (unit == nullptr)
			{
				throw std::exception(std::format(
					"ת����������ʧ��: %s => %s",
					entity->GetObjectType().GetName(),
					typeof(T).full_name()
				).c_str());
			}

			// ��Ϊ�ⲻ��һ��rpc��Ϣ���Է�����Ҫ֪����û��ִ�гɹ���
			// ��ǰ�ظ���Ϣ�����߶Է���Ϣ�յ��ˣ���ַľ�����⡣
			reply(&response);

			try
			{
				Run(unit, *request);
			}
			catch (std::exception& e)
			{
				LOG_ERROR("MActorLocationHandler error: ������Ϣ����:{} {}",
					typeof(Request).full_name(),
					e.what());
			}
			catch (...)
			{
				LOG_ERROR("MActorLocationHandler error: ������Ϣ����:{} δ֪����",
					typeof(Request).full_name());
			}
		}
		catch (std::exception& e)
		{
			LOG_ERROR("MActorLocationHandler error: ������Ϣʧ��:{} {}",
				typeof(Request).full_name(),
				e.what());
		}
		catch (...)
		{
			LOG_ERROR("MActorLocationHandler error: ������Ϣʧ��:{} δ֪����",
				typeof(Request).full_name());
		}
	
	}

	virtual void Run(const std::shared_ptr<T>& unit, Request& request) = 0;

	virtual const Type GetRequestType() const override { return typeof(Request); }
	virtual const Type GetResponseType() const override { return typeof(ActorResponse); }

};
