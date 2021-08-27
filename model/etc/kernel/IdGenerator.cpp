#include "IdGenerator.h"
#include "etc/Game.h"

IdGenerator* IdGenerator::Instance = nullptr;


int64_t IdGenerator::GenerateObjectID() {
	uint32_t now_time = TimeSinceThisYear();
	if (m_object_id_struct.time == 0)
	{
		// 第一次获取
		m_object_id_struct.process = Game::Options().AppId;
	}


	if (m_object_id_struct.time < now_time)
	{
		m_object_id_struct.time = now_time;
		m_object_id_struct.value = 0;
	}
	else {
		m_object_id_struct.value++;
	}

	if (m_object_id_struct.value >= ObjectIdStruct::MaxValue)
	{
		// 借下一秒时间
		m_object_id_struct.value = 0;
		m_object_id_struct.time++;
	}
	return m_object_id_struct.ToLong();
}

int64_t IdGenerator::GenerateID()
{
	uint32_t now_time = TimeSincePrjectStart();
	if (m_id_struct.time == 0)
	{
		// 第一次获取
		m_id_struct.process = Game::Options().AppId;
	}


	if (m_id_struct.time < now_time)
	{
		m_id_struct.time = now_time;
		m_id_struct.value = 0;
	}
	else {
		m_id_struct.value++;
	}

	if (m_id_struct.value >= IdStruct::MaxValue)
	{
		// 借下一秒时间
		m_id_struct.value = 0;
		m_id_struct.time++;
	}
	return m_id_struct.ToLong();
}