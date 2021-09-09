#pragma once 
#include "model/module/message.h"
#include "model/proto/EtcMsg.pb.h"
#include "model/demo/Entity/PlayerEntity.h"

namespace Hotfix
{
	void TestActor() {

		auto player = ObjectFactory::Create<PlayerEntity>();

		auto request = std::make_shared<ActorTestRequest>();
		request->set_a(102);
		request->set_b(201);
		for (int i = 0; i < 2; ++i)
		{
			time_t begin_time = Game::Time().NowServerMilliseconds();
			auto response = ActorMessageSenderComponent::Instance->Call<ActorTestResponse>(player->InstanceId(), request);
			time_t end_time = Game::Time().NowServerMilliseconds();
			LOG_INFO("耗时:{} 回复消息:{}", end_time - begin_time, response->ShortDebugString());
		}
		

	}
}