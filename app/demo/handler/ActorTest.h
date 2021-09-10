#pragma once 
#include "model/module/message.h"
#include "model/proto/DemoMsg.pb.h"
#include "model/demo/Entity/PlayerEntity.h"
#include "model/module/actor/MailBoxComponent.h"

namespace Hotfix
{
	void TestActor() {

		auto player = ObjectFactory::Create<PlayerEntity>();
		player->AddComponent<MailBoxComponent>();

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
		
		auto am = std::make_shared<ActorMessageTest>();
		am->set_msg_ctx(std::gb2312_to_utf8("你好啊"));
		ActorMessageSenderComponent::Instance->Send(player->InstanceId(), am);

	}
}