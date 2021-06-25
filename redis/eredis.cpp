#include "eredis.h"
#include <sstream>
#include <chrono>

#ifndef _WIN32
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#endif

#define DEFAULT_PING_TIME_GAP	20	//榛樿ping镞堕棿闂撮殧


#define TO(_a,_b)\
{\
std::stringstream _ss;\
_ss << _b;\
_ss >> _a;\
}

#define ADD_NUM_TO_A(str,count)\
{\
std::stringstream _ss;\
std::string _number;\
_ss << count;\
_ss >> _number;\
str += _number;\
}

eredis::eredis():
	m_NetRedis(nullptr),
	m_lastPingTime_s(0),
	m_pingTimeGap_s(DEFAULT_PING_TIME_GAP),
	m_Port(0)
{
	auto _timeNow = std::chrono::steady_clock::now();
	m_lastPingTime_s = std::chrono::duration_cast<std::chrono::seconds>(_timeNow.time_since_epoch()).count();
}

eredis::~eredis()
{
	if(m_NetRedis)
		net::NetRedisFree(m_NetRedis);
}

bool eredis::ConnectRedis(const std::string& sIp, const int32_t iPort, const std::string& sPassword)
{
	if (m_NetRedis)
		return false;
	// 杩炴帴鍒癛edis
	m_NetRedis = net::NetRedisConnectNonBlock(sIp.c_str(), iPort, DEFAULT_COMMAND_EXECUTION_TIME);
	if (!m_NetRedis)
		return false;
	if (!sPassword.empty())
	{
		// 瀵嗙爜璁よ瘉
		if (!net::NetRedisAuth(m_NetRedis, sPassword.c_str()))
		{
			net::NetRedisFree(m_NetRedis);
			m_NetRedis = nullptr;
			return false;
		}
	}
	net::NetRedisSetCallBack(m_NetRedis, CALLBACK_2(eredis::NetRedisCallBack, this));
	m_Ip = sIp;
	m_Port = iPort;
	m_Passward = sPassword;
	return true;
}

bool eredis::LoadLuaFile(const std::string& sFileName)
{
	if (!m_NetRedis)
		return false;
	std::string _luaName,_luaCode;
	// 铡婚櫎鐩綍 鍙缭鐣欐枃浠跺悕
	int _pos = sFileName.rfind('/');
	if (_pos == -1)
	{
		_pos = sFileName.rfind('\\');
	}
	if (_pos == -1)
	{
		_luaName = sFileName;
	}
	else {
		_pos++;
		_luaName = sFileName.substr(_pos, sFileName.size() - _pos);
	}
	// end
	// 銮峰彇鑴氭湰浠ｇ爜
	_luaCode = OpenFileWord(sFileName.c_str());
	if (_luaCode.empty())
		return false;
	// 鎻愪氦鑴氭湰鍒皉edis
	redisReply* _reply = net::NetRedisCommand(m_NetRedis, DEFAULT_COMMAND_EXECUTION_TIME, REDIS_COMMAND_SCRIPT_LOAD " %s", _luaCode.c_str());
	if (!_reply || _reply->type == REDIS_REPLY_ERROR)
	{
		if (_reply)
			freeReplyObject(_reply);
		return false;
	}
	if (_reply->type != REDIS_REPLY_STRING)
	{
		freeReplyObject(_reply);
		return false;
	}
	// 涓烘寚瀹氭枃浠跺悕璁剧疆sha1
	m_luaScript_umap[_luaName] = _reply->str;
	freeReplyObject(_reply);
	return true;
}

redisReply* eredis::RedisCommand(const char* format, ...)
{
	if (!m_NetRedis)
		return nullptr;
	redisReply* _ret;
	va_list _ap;
	va_start(_ap, format);
	_ret = net::NetRedisCommand(m_NetRedis, DEFAULT_COMMAND_EXECUTION_TIME, format, _ap);
	va_end(_ap);
	return _ret;
}

redisReply* eredis::RedisCommand(const int iTimeOut, const char* format, ...)
{
	if (!m_NetRedis)
		return nullptr;
	redisReply* _ret;
	va_list _ap;
	va_start(_ap, format);
	_ret = net::NetRedisCommand(m_NetRedis, iTimeOut, format, _ap);
	va_end(_ap);
	return _ret;
}

bool eredis::RedisCommandNonBlock(const char* format, ...)
{
	if (!m_NetRedis)
		return nullptr;
	bool _ret;
	va_list _ap;
	va_start(_ap, format);
	_ret = net::NetRedisCommandNonBlock(m_NetRedis, format, _ap);
	va_end(_ap);
	return _ret;
}

bool eredis::RedisAddCommand(const char* format, ...)
{
	if (!m_NetRedis)
		return nullptr;
	bool _ret;
	va_list _ap;
	va_start(_ap, format);
	_ret = net::NetRedisAddCommand(m_NetRedis, format, _ap);
	va_end(_ap);
	return _ret;
}

bool eredis::RedisWrite()
{
	if (!m_NetRedis)
		return nullptr;
	return net::NetRedisWrite(m_NetRedis);
}

redisReply* eredis::EvalSha(const std::string& sLuaName, const int32_t numkeys, const char* format, ...)
{
	redisReply* _ret;
	va_list _ap;
	va_start(_ap, format);
	_ret = EvalSha(sLuaName, DEFAULT_COMMAND_EXECUTION_TIME, numkeys, format, _ap);
	va_end(_ap);
	return _ret;
}

redisReply* eredis::EvalSha(const std::string& sLuaName, const int32_t iTimeOut, const int32_t numkeys, const char* format, ...)
{
	redisReply* _ret;
	va_list _ap;
	va_start(_ap, format);
	_ret = EvalSha(sLuaName, iTimeOut, numkeys,format, _ap);
	va_end(_ap);
	return _ret;
}

redisReply* eredis::EvalSha(const std::string& sLuaName, const int32_t iTimeOut, const int32_t numkeys, const char* format, va_list ap)
{
	if (sLuaName.empty() || !m_NetRedis)
		return nullptr;
	auto _findSha1 = m_luaScript_umap.find(sLuaName);
	if (_findSha1 == m_luaScript_umap.end())
		return nullptr;
	// 鎷兼帴锻戒护
	std::string _script = REDIS_COMMAND_EVALSHA " ";
	_script += _findSha1->second;
	_script += " ";
	ADD_NUM_TO_A(_script, numkeys);
	_script += " ";
	vsprintf(m_buffer, format, ap);
	_script += m_buffer;
	// end
	// 镓ц锻戒护
	return net::NetRedisCommand(m_NetRedis, iTimeOut, _script.c_str());
}

bool eredis::Subscribe(const std::string& sChannel)
{
	std::list<std::string> _allChannel;
	_allChannel.push_back(sChannel);
	return Subscribe(_allChannel);
}

bool eredis::Subscribe(const std::list<std::string>& AllChannel)
{
	return Subscribe(AllChannel, DEFAULT_COMMAND_EXECUTION_TIME);
}

bool eredis::Subscribe(const std::list<std::string>& AllChannel, const int32_t iTimeOut)
{
	if (AllChannel.empty() || !m_NetRedis)
		return false;
	// 鐢熸垚锻戒护
	std::string _StrCommand = REDIS_COMMAND_SUBSCRIBE " ";
	int32_t _i = 0;
	for (auto OneChannel : AllChannel)
	{
		if (_i)
			_StrCommand += " ";
		_StrCommand += OneChannel;
		++_i;
	}
	// end
	// 镓ц锻戒护
	redisReply* _reply;
	_reply = net::NetRedisCommand(m_NetRedis, iTimeOut, _StrCommand.c_str());
	if (!_reply)
		return false;
	if (_reply->type == REDIS_REPLY_ERROR)
	{
		if (_reply->str)
			m_NetRedis->ErrorMessage = _reply->str;
		freeReplyObject(_reply);
		return false;
	}
	freeReplyObject(_reply);
	// 璁板綍宸茶阒呯殑棰戦亾
	for (auto OneChannel : AllChannel)
		m_SubscribeAllChannel.insert(OneChannel);
	return true;
}

bool eredis::Publish(const std::string& sChannel, const std::string& sWord)
{
	return Publish(sChannel, sWord, DEFAULT_COMMAND_EXECUTION_TIME);
}

bool eredis::Publish(const std::string& sChannel, const std::string& sWord, const int32_t iTimeOut)
{
	if (!m_NetRedis)
		return false;
	// 镓ц锻戒护
	redisReply* _reply;
	_reply = net::NetRedisCommand(m_NetRedis, iTimeOut, REDIS_COMMAND_PUBLISH " %s %s",
		sChannel.c_str(), sWord.c_str());
	if (!_reply)
		return false;
	if (_reply->type == REDIS_REPLY_ERROR)
	{
		if (_reply->str)
			m_NetRedis->ErrorMessage = _reply->str;
		freeReplyObject(_reply);
		return false;
	}
	freeReplyObject(_reply);
	return true;
}

bool eredis::PublishNonBlock(const std::string& sChannel, const std::string& sWord)
{
	if (!m_NetRedis)
		return false;
	return net::NetRedisCommandNonBlock(m_NetRedis, REDIS_COMMAND_PUBLISH " %s %s",
		sChannel.c_str(), sWord.c_str());
}

bool eredis::Unsubscribe(const std::string& sChannel)
{
	std::list<std::string> _allChannel;
	_allChannel.push_back(sChannel);
	return Unsubscribe(_allChannel);
}

bool eredis::Unsubscribe(const std::list<std::string>& AllChannel)
{
	return Unsubscribe(AllChannel, DEFAULT_COMMAND_EXECUTION_TIME);
}

bool eredis::Unsubscribe(const std::list<std::string>& AllChannel, const int32_t iTimeOut)
{
	if (AllChannel.empty() || !m_NetRedis)
		return false;
	// 鐢熸垚锻戒护
	std::string _StrCommand = REDIS_COMMAND_UNSUBSCRIBE " ";
	int32_t _i = 0;
	for (auto OneChannel : AllChannel)
	{
		if (_i)
			_StrCommand += " ";
		_StrCommand += OneChannel;
		++_i;
	}
	// end
	// 镓ц锻戒护
	redisReply* _reply;
	_reply = net::NetRedisCommand(m_NetRedis, iTimeOut, _StrCommand.c_str());
	if (!_reply)
		return false;
	if (_reply->type == REDIS_REPLY_ERROR)
	{
		if (_reply->str)
			m_NetRedis->ErrorMessage = _reply->str;
		freeReplyObject(_reply);
		return false;
	}
	freeReplyObject(_reply);
	// 绉婚櫎宸茶阒呯殑棰戦亾
	for (auto OneChannel : AllChannel)
		m_SubscribeAllChannel.erase(OneChannel);
	return true;
}

void eredis::Update()
{
	if(m_NetRedis)
		net::NetRedisReadAndParse(m_NetRedis);
}

void eredis::Ping()
{
	auto _timeNow = std::chrono::steady_clock::now();
	int64_t _time = std::chrono::duration_cast<std::chrono::seconds>(_timeNow.time_since_epoch()).count();
	if (_time - m_lastPingTime_s < m_pingTimeGap_s)
	{
		return;
	}
	m_lastPingTime_s = _time;
	if (!m_NetRedis)
		goto reconnect;		// 璺宠浆鍒皉edis閲嶈繛

	if (!net::NetRedisPing(m_NetRedis))
	{
		// 涓岩edis鏂紑杩炴帴
		net::NetRedisFree(m_NetRedis);
		m_NetRedis = nullptr;
		goto reconnect;		// 璺宠浆鍒皉edis閲嶈繛
	}

	return;

reconnect:
	// 閲嶈繛redis
	{
		if (m_Ip.empty())
			return;
		if (!ConnectRedis(m_Ip, m_Port, m_Passward))
			return;
		// 閲嶆柊璁㈤槄棰戦亾
		std::list<std::string> _allChannel;
		for (auto OneChannel : m_SubscribeAllChannel)
			_allChannel.push_back(OneChannel);
		Subscribe(_allChannel);
	}
}

void eredis::NetRedisCallBack(redisReply* pReply, net::NetRedis_t* pSelf)
{
	if (!pReply)
		return;
	switch (pReply->type)
	{
	case REDIS_REPLY_ARRAY:
	{
		// 棰戦亾娑堟伅鍒拌揪澶勭悊
		if (pReply->elements == 3)
		{
			
			if (!pReply->element[0] || !pReply->element[0]->str ||m_StrMessage.compare(pReply->element[0]->str))
				return;
			if (!pReply->element[1] || !pReply->element[1]->str)
				return;
			if (!pReply->element[2] || !pReply->element[2]->str)
				return;
			if (m_ChannelCallBack)
				m_ChannelCallBack(pReply->element[1]->str, pReply->element[2]->str, pReply->element[2]->len, this);
		}

	}
	break;
	}
}

std::string eredis::OpenFileWord(const char* sFile)
{
	FILE* _fp = fopen(sFile, "rb");
	if (NULL == _fp)
		return "";

	struct stat _FileStat;
	fstat(fileno(_fp), &_FileStat);
	char* _buf = new char[_FileStat.st_size];

	fread(_buf, _FileStat.st_size, 1, _fp);
	std::string _word;
	_word.append(_buf, _FileStat.st_size);
	fclose(_fp);
	delete[]_buf;
	_buf = NULL;
	return _word;
}