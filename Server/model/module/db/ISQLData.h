#pragma once
#include <stdint.h>
#include <string>
#include <memory>


namespace Model
{
	class ISQLData
	{
	public:
		using ptr = std::shared_ptr<ISQLData>;

		virtual int8_t GetInt8(const int idx) const = 0;
		virtual int16_t GetInt16(const int idx) const = 0;
		virtual int32_t GetInt32(const int idx) const = 0;
		virtual int64_t GetInt64(const int idx) const = 0;
		virtual uint8_t GetUInt8(const int idx) const = 0;
		virtual uint16_t GetUInt16(const int idx) const = 0;
		virtual uint32_t GetUInt32(const int idx) const = 0;
		virtual uint64_t GetUInt64(const int idx) const = 0;
		virtual float GetFloat(const int idx) const = 0;
		virtual double GetDouble(const int idx) const = 0;
		virtual std::string GetString(const int idx) const = 0;
		virtual time_t GetTime(const int idx) const = 0;

		virtual int8_t GetInt8(const std::string& key) = 0;
		virtual int16_t GetInt16(const std::string& key) = 0;
		virtual int32_t GetInt32(const std::string& key) = 0;
		virtual int64_t GetInt64(const std::string& key) = 0;
		virtual uint8_t GetUInt8(const std::string& key) = 0;
		virtual uint16_t GetUInt16(const std::string& key) = 0;
		virtual uint32_t GetUInt32(const std::string& key) = 0;
		virtual uint64_t GetUInt64(const std::string& key) = 0;
		virtual float GetFloat(const std::string& key) = 0;
		virtual double GetDouble(const std::string& key) = 0;
		virtual std::string GetString(const std::string& key) = 0;
		virtual time_t GetTime(const std::string& key) = 0;

		virtual bool Next() = 0;


	};
}