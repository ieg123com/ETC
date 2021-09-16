#include "MySQL.h"
#include "other/string/str.h"
#include "base/log/ServerLog.h"


namespace Model
{


	MYSQL* mysql_init(const std::map<std::string, std::string>& params, const int& timeout) 
	{
		MYSQL* mysql = ::mysql_init(nullptr);
		if (mysql == nullptr)
		{
			LOG_ERROR("mysql_init error");
			return nullptr;
		}
		bool close = false;
		mysql_options(mysql, MYSQL_OPT_RECONNECT, &close);
		mysql_options(mysql, MYSQL_SET_CHARSET_NAME, "utf8mb4");

		if (mysql_real_connect(mysql, host.c_str(), user.c_str(), passwd.c_str()
			, dbname.c_str(), port, NULL, 0) == nullptr) {
			SYLAR_LOG_ERROR(g_logger) << "mysql_real_connect(" << host
				<< ", " << port << ", " << dbname
				<< ") error: " << mysql_error(mysql);
			mysql_close(mysql);
			return nullptr;
		}
		return mysql;



	}




	int8_t MySQLRes::GetInt8(const int idx) const
	{
		return std::to<int8_t>(m_row[idx]);
	}

	int16_t MySQLRes::GetInt16(const int idx) const
	{
		return std::to<int16_t>(m_row[idx]);
	}

	int32_t MySQLRes::GetInt32(const int idx) const
	{
		return std::to<int32_t>(m_row[idx]);
	}

	int64_t MySQLRes::GetInt64(const int idx) const
	{
		return std::to<int64_t>(m_row[idx]);
	}

	uint8_t MySQLRes::GetUInt8(const int idx) const
	{
		return std::to<uint8_t>(m_row[idx]);
	}

	uint16_t MySQLRes::GetUInt16(const int idx) const
	{
		return std::to<uint16_t>(m_row[idx]);
	}

	uint32_t MySQLRes::GetUInt32(const int idx) const
	{
		return std::to<uint32_t>(m_row[idx]);
	}

	uint64_t MySQLRes::GetUInt64(const int idx) const
	{
		return std::to<uint64_t>(m_row[idx]);
	}

	float MySQLRes::GetFloat(const int idx) const
	{
		return std::to<float>(m_row[idx]);
	}

	double MySQLRes::GetDouble(const int idx) const
	{
		return std::to<double>(m_row[idx]);
	}

	std::string MySQLRes::GetString(const int idx) const
	{
		return m_row[idx];
	}

	time_t MySQLRes::GetTime(const int idx) const
	{
		return std::to<time_t>(m_row[idx]);
	}

	bool MySQLRes::Next()
	{
		if (m_row = mysql_fetch_row(m_res))
		{
			return true;
		}
		return false;
	}






	MySQL::MySQL(const std::map<std::string, std::string>& args):
		m_params(args)
	{

	}


	bool MySQL::Connect()
	{
		
	}

	bool MySQL::Ping()
	{

	}

	ISQLData::ptr MySQL::Query(const char* format, ...)
	{

	}

	ISQLData::ptr MySQL::Query(const char* format, va_list ap)
	{

	}

	ISQLData::ptr MySQL::Query(const std::string& sql)
	{

	}
}