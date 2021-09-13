#include "IdGenerator.h"
#include "etc/Game.h"

namespace Model
{
	IdGenerator* IdGenerator::Instance = nullptr;


	InstanceID IdGenerator::GenerateInstanceId() {
		uint32_t now_time = TimeSinceThisYear();
		if (m_instance_id_struct.time == 0)
		{
			// 第一次获取
			m_instance_id_struct.process = Game::Options().ProcessId;
		}


		if (m_instance_id_struct.time < now_time)
		{
			m_instance_id_struct.time = now_time;
			m_instance_id_struct.value = 0;
		}
		else {
			m_instance_id_struct.value++;
		}

		if (m_instance_id_struct.value >= InstanceIdStruct::MaxValue)
		{
			// 借下一秒时间
			m_instance_id_struct.value = 0;
			m_instance_id_struct.time++;
		}
		return m_instance_id_struct.ToLong();
	}

	ID IdGenerator::GenerateId()
	{
		uint32_t now_time = TimeSincePrjectStart();
		if (m_id_struct.time == 0)
		{
			// 第一次获取
			m_id_struct.process = Game::Options().ProcessId;
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

	int64_t IdGenerator::GenerateUnitId()
	{
		uint32_t now_time = TimeSincePrjectStart();
		if (m_unit_id_struct.time == 0)
		{
			// 第一次获取
			m_unit_id_struct.process = Game::Options().ProcessId;
		}


		if (m_unit_id_struct.time < now_time)
		{
			m_unit_id_struct.time = now_time;
			m_unit_id_struct.value = 0;
		}
		else {
			m_unit_id_struct.value++;
		}

		if (m_unit_id_struct.value >= UnitIdStruct::MaxValue)
		{
			// 借下一秒时间
			m_unit_id_struct.value = 0;
			m_unit_id_struct.time++;
		}
		return m_unit_id_struct.ToLong();
	}
}