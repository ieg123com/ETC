#pragma once
#include <stdint.h>
#include <chrono>
#include "other/time/Time.h"
#include "GameDefinition.h"


struct IdStruct
{
	static const uint32_t Mask18bit = (uint32_t)(0x3ffff);
	static const uint32_t Mask16bit = (uint32_t)(0xffff);
	static const uint32_t MaxValue = (uint32_t)(0xffff);

	uint32_t	time;		// 时间		30bit	34年
	int32_t		process;	// 进程id	18bit
	uint32_t	value;		// 递增值	16bit

	IdStruct() {
		time = 0;
		process = 0;
		value = 0;
	}

	IdStruct(const int64_t id) {
		int64_t result = id;
		value = (uint32_t)(result & IdStruct::Mask16bit);
		result >>= 16;
		process = (int32_t)(result & IdStruct::Mask18bit);
		result >>= 18;
		time = (uint32_t)result;
	}

	IdStruct(const uint32_t t, const int32_t pid, const uint32_t v) {
		time = t;
		process = pid;
		value = v;
	}

	int64_t ToLong() {
		int64_t result = value;
		result |= (int64_t)process << 16;
		result |= (int64_t)time << (18 + 16);
		return result;
	}

	std::string ToString() {
		return "time:" + std::to_string(time) + " process:" + std::to_string(process) + " value:" + std::to_string(value);
	}
};



// 实例id结构体
struct InstanceIdStruct
{
	static const uint32_t MaxValue = (uint32_t)(0x3ffff);

	uint32_t	time;		// 时间		28bit	8年
	int32_t		process;	// 进程id	18bit	262k
	uint32_t	value;		// 递增值	18bit

	InstanceIdStruct() {
		time = 0;
		process = 0;
		value = 0;
	}

	InstanceIdStruct(const int64_t id) {
		int64_t result = id;
		value = (uint32_t)(result & IdStruct::Mask18bit);
		result >>= 18;
		process = (int32_t)(result & IdStruct::Mask18bit);
		result >>= 18;
		time = (uint32_t)result;
	}

	InstanceIdStruct(const uint32_t t, const int32_t pid, const uint32_t v){
		time = t;
		process = pid;
		value = v;
	}

	// 给固定的对象使用
	InstanceIdStruct(const int32_t pid, const uint32_t v) {
		time = 0;
		process = pid;
		value = v;
	}

	int64_t ToLong() {
		int64_t result = value;
		result |= (int64_t)process << 18;
		result |= (int64_t)time << (18 + 18);
		return result;
	}

	std::string ToString() {
		return "time:" + std::to_string(time) + " process:" + std::to_string(process) + " value:" + std::to_string(value);
	}

};


// 实体id结构体
struct UnitIdStruct
{
	static const uint32_t MaxValue = (uint32_t)(0xffff);

	uint32_t	time;		// 30bit	34年
	uint16_t	zone;		// 10bit	1024区
	uint8_t		process;	// 8bit		每个区支持 256 进程
	uint16_t	value;		// 16bit	每秒产生 65536 id

	int64_t ToLong(){
		uint64_t result = 0;
		result |= value;
		result |= (uint64_t)process << 16;
		result |= (uint64_t)zone << 24;
		result |= (uint64_t)time << 34;
		return (int64_t)result;
	}

	UnitIdStruct() {
		time = 0;
		zone = 0;
		process = 0;
		value = 0;
	}

	UnitIdStruct(const int32_t z, const int32_t pid, const uint32_t t, const uint16_t val){
		time = t;
		process = (uint8_t)(pid % 256);
		value = val;
		zone = (uint16_t)z;
	}

	UnitIdStruct(const int64_t id){
		uint64_t result = (uint64_t)id;
		value = (uint16_t)(result & UINT16_MAX);
		result >>= 16;
		process = (uint8_t)(result & UINT8_MAX);
		result >>= 8;
		zone = (uint16_t)(result & 0x03ff);
		result >>= 10;
		time = (uint32_t)result;
	}

	std::string ToString(){
		return "time:" + std::to_string(time) + " zone:" + std::to_string(zone) + " process:" + std::to_string(process) + " value:" + std::to_string(value);
	}

	static int32_t GetUnitZone(const int64_t unitId){
		return (int32_t)((unitId >> 24) & 0x03ff); // 取出10bit
	}
};



class IdGenerator
{
	time_t	m_epoch_prject_start;
	time_t	m_epoch_this_year;

	InstanceIdStruct	m_instance_id_struct;
	IdStruct			m_id_struct;
	UnitIdStruct		m_unit_id_struct;

public:

	static IdGenerator* Instance;

	IdGenerator() {
		Time time;
		time.today().mon(0).day(1);
		m_epoch_prject_start = 1609430400;	// 2021-01-01 00:00:00
		m_epoch_this_year = time.to_seconds_count();
	}


	uint32_t TimeSincePrjectStart() const {
		time_t now_time = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
		return (uint32_t)(now_time - m_epoch_prject_start);
	}

	uint32_t TimeSinceThisYear() const {
		time_t now_time = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
		return (uint32_t)(now_time - m_epoch_this_year);
	}
	
	int64_t GenerateInstanceId();

	int64_t GenerateId();

	int64_t GenerateUnitId();



	static int64_t GenInstanceId();
	static int64_t GenId();
	static int64_t GenUnitId();


};


inline int64_t IdGenerator::GenInstanceId() {
	return IdGenerator::Instance->GenerateInstanceId();
}

inline int64_t IdGenerator::GenId() {
	return IdGenerator::Instance->GenerateId();
}

inline int64_t IdGenerator::GenUnitId() {
	return IdGenerator::Instance->GenerateUnitId();
}