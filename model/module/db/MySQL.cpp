#include "MySQL.h"
#include "other/string/str.h"
#include "other/string/Param.h"
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

		uint32_t port = std::GetParamValue<uint32_t>(params, "port");
		std::string host = std::GetParamValue(params, "host");
		std::string user = std::GetParamValue(params, "user");
		std::string passwd = std::GetParamValue(params, "passwd");
		std::string dbname = std::GetParamValue(params, "dbname");
		if (mysql_real_connect(mysql, host.c_str(), user.c_str(), passwd.c_str()
			, dbname.c_str(), port, NULL, 0) == nullptr) {
			LOG_ERROR("mysql_real_connect({}:{},{}) error:{}", host, port, dbname, mysql_error(mysql));
			mysql_close(mysql);
			return nullptr;
		}
		return mysql;
	}


	MySQLRes::MySQLRes(MYSQL_RES* res, const int erron, const char* error):
		m_erron(erron),
		m_error(error)
	{
		m_res.reset(res, mysql_free_result);
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

	int8_t MySQLRes::GetInt8(const std::string& key)
	{
		return GetInt8(GetIndexByKey(key));
	}

	int16_t MySQLRes::GetInt16(const std::string& key)
	{
		return GetInt16(GetIndexByKey(key));
	}

	int32_t MySQLRes::GetInt32(const std::string& key)
	{
		return GetInt32(GetIndexByKey(key));
	}

	int64_t MySQLRes::GetInt64(const std::string& key)
	{
		return GetInt64(GetIndexByKey(key));
	}

	uint8_t MySQLRes::GetUInt8(const std::string& key)
	{
		return GetUInt8(GetIndexByKey(key));
	}

	uint16_t MySQLRes::GetUInt16(const std::string& key)
	{
		return GetUInt16(GetIndexByKey(key));
	}

	uint32_t MySQLRes::GetUInt32(const std::string& key)
	{
		return GetUInt32(GetIndexByKey(key));
	}

	uint64_t MySQLRes::GetUInt64(const std::string& key)
	{
		return GetUInt64(GetIndexByKey(key));
	}

	float MySQLRes::GetFloat(const std::string& key)
	{
		return GetFloat(GetIndexByKey(key));
	}

	double MySQLRes::GetDouble(const std::string& key)
	{
		return GetDouble(GetIndexByKey(key));
	}

	std::string MySQLRes::GetString(const std::string& key)
	{
		return GetString(GetIndexByKey(key));
	}

	time_t MySQLRes::GetTime(const std::string& key)
	{
		return GetTime(GetIndexByKey(key));
	}


	bool MySQLRes::Next()
	{
		if (m_row = mysql_fetch_row(m_res.get()))
		{
			return true;
		}
		return false;
	}

	bool MySQLRes::Foreach(const std::function<data_cb>& cb)
	{
		MYSQL_ROW row;
		size_t field_count = mysql_num_fields(m_res.get());
		size_t row_no = 0;
		while ((row = mysql_fetch_row(m_res.get()))) {
			if (!cb(row,field_count,row_no++)) {
				break;
			}
		}
		return true;
	}

	int MySQLRes::GetIndexByKey(const std::string& key)
	{
		if (m_key_index.empty())
		{
			// Fetch name of column
			size_t fields = mysql_num_fields(m_res.get());
			MYSQL_FIELD* field = mysql_fetch_field(m_res.get());
			for (int col = 0; col < fields; ++col)
			{
				m_key_index[field[col].name] = col;
			}
		}
		auto found = m_key_index.find(key);
		if (found == m_key_index.end())
		{
			throw std::exception(std::format("key '%s' not found", key.c_str()).c_str());
		}
		return found->second;
	}






	MySQL::MySQL(const std::map<std::string, std::string>& args) :
		m_params(args),
		m_has_error(false)
	{
		m_cmd.resize(1024);
	}


	bool MySQL::Connect()
	{
		if (m_mysql && !m_has_error)
		{
			return true;
		}

		MYSQL *mysql = mysql_init(m_params,false);
		if (mysql == nullptr)
		{
			m_has_error = true;
			return false;
		}
		m_mysql.reset(mysql, mysql_close);
		m_has_error = false;
		return true;
	}

	bool MySQL::Ping()
	{
		if (!m_mysql)
		{
			return false;
		}
		if (mysql_ping(m_mysql.get()))
		{
			m_has_error = true;
			return false;
		}
		m_has_error = false;
		return true;
	}

	int MySQL::Execute(const char* format, ...)
	{
		va_list ap;
		va_start(ap, format);
		int rt = Execute(format, ap);
		va_end(ap);
		return rt;
	}

	int MySQL::Execute(const char* format, va_list ap)
	{
		int ret;
		va_list new_ap = ap;
		while ((ret = vsnprintf(&m_cmd[0], m_cmd.size(), format, new_ap)) > m_cmd.size())
		{
			m_cmd.resize(m_cmd.size() * 2);
			new_ap = ap;
		}
		ret = mysql_query(m_mysql.get(), m_cmd.c_str());
		if (ret)
		{
			m_has_error = true;
			return ret;
		}
		else {
			m_has_error = false;
		}
		return ret;
	}

	int MySQL::Execute(const std::string& sql)
	{
		int ret = mysql_query(m_mysql.get(), m_cmd.c_str());
		if (ret)
		{
			m_has_error = true;
			return ret;
		}
		else {
			m_has_error = false;
		}
		return ret;
	}

	MySQLRes::ptr MySQL::Query(const char* format, ...)
	{
		va_list ap;
		va_start(ap, format);
		MySQLRes::ptr sql_data = Query(format, ap);
		va_end(ap);
		return sql_data;
	}

	MySQLRes::ptr MySQL::Query(const char* format, va_list ap)
	{
		int ret;
		va_list new_ap = ap;
		while ((ret = vsnprintf(&m_cmd[0], m_cmd.size(), format, new_ap)) > m_cmd.size())
		{
			m_cmd.resize(m_cmd.size() * 2);
			new_ap = ap;
		}
		
		if (ret = mysql_query(m_mysql.get(), m_cmd.c_str()))
		{
			m_has_error = true;
			return nullptr;
		}

		MYSQL_RES* res = mysql_store_result(m_mysql.get());
		if (res == nullptr)
		{
			m_has_error = true;
			return nullptr;
		}
		m_has_error = false;
		return std::make_shared<MySQLRes>(res, mysql_errno(m_mysql.get()), mysql_error(m_mysql.get()));
	}

	MySQLRes::ptr MySQL::Query(const std::string& sql)
	{
		m_cmd = sql;
		if (int ret = mysql_query(m_mysql.get(), m_cmd.c_str()))
		{
			m_has_error = true;
			return nullptr;
		}

		MYSQL_RES* res = mysql_store_result(m_mysql.get());
		if (res == nullptr)
		{
			m_has_error = true;
			return nullptr;
		}
		m_has_error = false;
		return std::make_shared<MySQLRes>(res, mysql_errno(m_mysql.get()), mysql_error(m_mysql.get()));
	}
}