#pragma once
#include "module/message.h"

namespace Model
{
	class ActorLocationSender;


	// 带有地址的Actor消息调用组件
	class ActorLocationSenderComponent :
		public Component
	{
		class rpc_exception :
			public ::std::exception
		{
		public:
			ETC_ERR Error;
			rpc_exception(const ETC_ERR error, char const* const message) : Error(error), ::std::exception(message) {}
		};


	public:
		static ActorLocationSenderComponent* Instance;

		static const time_t TIMEOUT_TIME = 60 * 1000;

		int64_t CheckTimer;

		std::shared_ptr<ActorLocationSender> GetOrCreate(const ID key);

		void Remove(const ID key);

		void Send(const ID key, const std::shared_ptr<IActorRequest>& message);

		template<typename T>
		std::shared_ptr<T> Call(const ID key, const std::shared_ptr<IActorRequest>& message) {
			auto msg_rpo = __Call(key, message);
			if (auto response = std::dynamic_pointer_cast<T>(msg_rpo))
			{
				return response;
			}
			throw std::exception(std::format("无法转换类型: %s => %s",
				msg_rpo->GetType().full_name(),
				typeof(T).full_name()).c_str());
		}


	private:

		std::shared_ptr<IActorResponse> __Call(const ID key, const std::shared_ptr<IActorRequest>& message);

		std::shared_ptr<IActorResponse> __CallInner(const std::shared_ptr<ActorLocationSender>& actor_location_sender, const std::shared_ptr<IActorRequest>& message);

	};


}