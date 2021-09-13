#include "ActorLocationSenderComponent.h"
#include "LocationProxyComponent.h"
#include "ActorLocationSender.h"
#include "module/message/OpcodeTypeComponent.h"
#include "module/actor/ActorMessageSenderComponent.h"
#include "coroutine.h"


namespace Model
{
	ActorLocationSenderComponent* ActorLocationSenderComponent::Instance = nullptr;


	std::shared_ptr<ActorLocationSender> ActorLocationSenderComponent::GetOrCreate(const ID key)
	{
		if (auto actor_location = GetChild<ActorLocationSender>(key))
		{
			return actor_location;
		}
		// 创建新的 ActorLocationSender
		return ObjectFactory::CreateWithHostAndId<ActorLocationSender>(Self(), key);
	}

	void ActorLocationSenderComponent::Remove(const ID key)
	{
		if (auto actor_location = GetChild<ActorLocationSender>(key))
		{
			actor_location->Dispose();
		}
	}

	void ActorLocationSenderComponent::Send(const ID key, const std::shared_ptr<IActorRequest>& message)
	{
		auto self = Get<ActorLocationSenderComponent>();
		go[=]{ self->__Call(key, message); };
	}


	std::shared_ptr<IActorResponse> ActorLocationSenderComponent::__Call(const ID key, const std::shared_ptr<IActorRequest>& message)
	{
		auto actor_location_sender = GetOrCreate(key);
		InstanceID instance_id = actor_location_sender->InstanceId();
		std::lock_guard<co::CoMutex> lock(actor_location_sender->Lock);
		if (instance_id != actor_location_sender->InstanceId())
		{
			throw rpc_exception(ETC_ERR::ActorTimeout,
				std::format("message type: %s  message: %s",
					message->GetType().full_name(),
					message->ShortDebugString().c_str()).c_str());
		}

		try {
			return __CallInner(actor_location_sender, message);
		}
		catch (rpc_exception& e) {
			Remove(key);
			throw e;
		}
		catch (std::exception& e) {
			Remove(key);
			throw e;
		}
		catch (...) {
			Remove(key);
			throw std::exception("未知错误");
		}
	}

	std::shared_ptr<IActorResponse> ActorLocationSenderComponent::__CallInner(const std::shared_ptr<ActorLocationSender>& actor_location_sender, const std::shared_ptr<IActorRequest>& message)
	{
		int32_t fail_times = 0;
		actor_location_sender->LastSendTime = Game::Time().NowServerMilliseconds();
		InstanceID instance_id = actor_location_sender->InstanceId();
		while (true)
		{
			if (actor_location_sender->ActorId == 0)
			{
				actor_location_sender->ActorId = LocationProxyComponent::Instance->Get(actor_location_sender->Id);
				if (actor_location_sender->InstanceId() != instance_id)
				{
					// 获取 ActorLocation 期间，	sender 对象已经被销毁了
					throw rpc_exception(ETC_ERR::ActorLocationSenderTimeout, std::format("actor send message fail, , message type: %s", message->GetType().full_name()).c_str());
				}
			}
			if (actor_location_sender->ActorId == 0)
			{
				// 没有找到ActorId
				auto response = OpcodeTypeComponent::CreateResponseInstanceTry<IActorResponse>(message->GetOpcode());
				response->SetRpcId(message->GetRpcId());
				response->SetError((int32_t)ETC_ERR::NotFoundActor);
				return response;
			}
			auto response = ActorMessageSenderComponent::Instance->Call(actor_location_sender->ActorId, message, false);
			switch ((ETC_ERR)response->GetError())
			{
			case ETC_ERR::NotFoundActor:
			{
				++fail_times;
				if (fail_times > 20)
				{
					LOG_DEBUG("actor send message fail,fail times: {}  actorid: {}",
						fail_times, actor_location_sender->ActorId);
					actor_location_sender->Error = ETC_ERR::NotFoundActor;
					return response;
				}

				co_sleep(500);
				if (actor_location_sender->InstanceId() != instance_id)
				{
					// 等待期间 sender 已销毁
					throw rpc_exception(ETC_ERR::ActorLocationSenderTimeout, std::format("actor send message fail, , message type: %s", message->GetType().full_name()).c_str());
				}

				actor_location_sender->ActorId = 0;
				break;
			}
			case ETC_ERR::ActorNoMailBoxComponent:
			case ETC_ERR::ActorTimeout:
				throw rpc_exception((ETC_ERR)response->GetError(), std::format("ActorLocationSender error: message type: %s", message->GetType().full_name()).c_str());
			}
			if (IsRpcNeedThrowException((ETC_ERR)response->GetError()))
			{
				throw rpc_exception((ETC_ERR)response->GetError(),
					std::format("ActorLocationSender error: message type: %s  message: %s",
						response->GetMessage().c_str(),
						message->GetType().full_name()).c_str());
			}
			return response;
		}

	}

}