#pragma once
#include <map>
#include "ISQLData.h"
#pragma once
#define WIN32_LEAN_AND_MEAN 
#include "mysql/mysql.h"

#ifdef _WIN32
#pragma comment(lib, "libmysql.lib")
#endif


namespace Model
{
	class MySQLRes :public ISQLData
	{
	public:


		virtual int8_t GetInt8(const int idx) const override;
		virtual int16_t GetInt16(const int idx) const override;
		virtual int32_t GetInt32(const int idx) const override;
		virtual int64_t GetInt64(const int idx) const override;
		virtual uint8_t GetUInt8(const int idx) const override;
		virtual uint16_t GetUInt16(const int idx) const override;
		virtual uint32_t GetUInt32(const int idx) const override;
		virtual uint64_t GetUInt64(const int idx) const override;
		virtual float GetFloat(const int idx) const override;
		virtual double GetDouble(const int idx) const override;
		virtual std::string GetString(const int idx) const override;
		virtual time_t GetTime(const int idx) const override;

		virtual void Next() override;

	private:
		
		MYSQL_ROW	m_row;
		MYSQL_RES*	m_res;

	};



	class MySQL
	{
	public:
		MySQL(const std::map<std::string, std::string>& args);

		bool Connect();
		bool Ping();

		ISQLData::ptr Query(const char* format, ...);
		ISQLData::ptr Query(const char* format, va_list ap);
		ISQLData::ptr Query(const std::string& sql);



	private:
		MYSQL	m_mysql;



	};



}