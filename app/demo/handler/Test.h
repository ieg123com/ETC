#include "ActorTest.h"
#include "ActorLocationTest.h"
#include "model/module/db/MySQLSchedulerComponent.h"


namespace Hotfix
{

	void StartTest() {
		LOG_INFO("==========> ¿ªÊ¼²âÊÔ <===========");
		TestActor();
		TestActorLocation();

		auto mysql = MySQLSchedulerComponent::Instance->Get(2);
		
		auto res = mysql->Query("select * from gamerole limit 10;");

		while (res->Next())
		{
			LOG_INFO("game_name: {}", res->GetString("game_name"));
		}
		
// 		res->Foreach([](MYSQL_ROW row, size_t field_count, size_t row_no)->bool {
// 			LOG_INFO("row {}",std::to<int32_t>(row[0]));
// 			return true;
// 			});

		LOG_INFO("Ok");
	}


}