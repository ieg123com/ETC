#pragma once
#include <map>
#include <functional>
#include <unordered_map>
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
		using ptr = std::shared_ptr<MySQLRes>;
		using data_cb = bool(MYSQL_ROW row,size_t field_count,size_t row_no);

		MySQLRes(MYSQL_RES* res,const int erron,const char* error);

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

		virtual int8_t GetInt8(const std::string& key) override;
		virtual int16_t GetInt16(const std::string& key) override;
		virtual int32_t GetInt32(const std::string& key) override;
		virtual int64_t GetInt64(const std::string& key) override;
		virtual uint8_t GetUInt8(const std::string& key) override;
		virtual uint16_t GetUInt16(const std::string& key) override;
		virtual uint32_t GetUInt32(const std::string& key) override;
		virtual uint64_t GetUInt64(const std::string& key) override;
		virtual float GetFloat(const std::string& key) override;
		virtual double GetDouble(const std::string& key) override;
		virtual std::string GetString(const std::string& key) override;
		virtual time_t GetTime(const std::string& key) override;


		virtual bool Next() override;

		bool Foreach(const std::function<data_cb>& cb);
	private:
		int GetIndexByKey(const std::string& key);

	private:
		
		int		m_erron;
		std::string m_error;

		MYSQL_ROW	m_row;
		std::unordered_map<std::string, int>	m_key_index;

		std::shared_ptr<MYSQL_RES>	m_res;
		

		friend class MySQL;
	};



	class MySQL
	{
	public:
		MySQL(const std::map<std::string, std::string>& args);

		bool Connect();
		bool Ping();

		int Execute(const char* format, ...);
		int Execute(const char* format, va_list ap);
		int Execute(const std::string& sql);

		MySQLRes::ptr Query(const char* format, ...);
		MySQLRes::ptr Query(const char* format, va_list ap);
		MySQLRes::ptr Query(const std::string& sql);



	private:
		std::map<std::string, std::string> m_params;
		std::shared_ptr<MYSQL>	m_mysql;

		std::string m_cmd;

		// 有错误
		bool	m_has_error;
	};



}