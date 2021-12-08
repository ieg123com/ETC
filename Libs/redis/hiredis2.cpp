#include "hiredis2.h"

void NetRedisInit(net::NetRedis_t* pNetRedis);

net::NetRedis_t* net::NetRedisConnectNonBlock(const char* sIp, const int iPort, const int iTimeOut)
{
	redisContext* _c = nullptr;
	net::NetRedis_t* _redis = nullptr;
	timeval _time;
	_time.tv_sec = iTimeOut / 1000;
	_time.tv_usec = iTimeOut % 1000 * 1000;
	_c = redisConnectNonBlockWithTimeout(sIp, iPort, _time);
	if (_c && _c->err == REDIS_OK)
	{
		// 连接成功
		_redis = new net::NetRedis_t;
		NetRedisInit(_redis);
		_redis->pRedisContext = _c;
		_redis->Ip = sIp;
		_redis->Port = iPort;
	}
	return _redis;
}

bool net::NetRedisReconnect(net::NetRedis_t* pNetRdis)
{
	redisContext* _c = nullptr;
	timeval _time;
	_time.tv_sec = 3;
	_time.tv_usec = 0;
	_c = redisConnectNonBlockWithTimeout(pNetRdis->Ip.c_str(), pNetRdis->Port, _time);
	if (!_c || _c->err != REDIS_OK)
		return false;
	if (pNetRdis->pRedisContext)
		redisFree(pNetRdis->pRedisContext);
	pNetRdis->pRedisContext = _c;
	return true;
}

redisReply* net::NetRedisCommand(net::NetRedis_t* pNetRedis, const int iTimeOut, const char* format, va_list ap)
{
	NetRedisReadAndParse(pNetRedis);
	int _error = REDIS_OK;
	_error = redisvAppendCommand(pNetRedis->pRedisContext, format, ap);
	if (_error != REDIS_OK)
		return nullptr;
	return NetRedisGetReply(pNetRedis, iTimeOut);
}

redisReply* net::NetRedisCommand(net::NetRedis_t* pNetRedis, const int iTimeOut, const char* format, ...)
{
	redisReply* _ret;
	va_list ap;
	va_start(ap, format);
	_ret = NetRedisCommand(pNetRedis, iTimeOut, format, ap);
	va_end(ap);
	return _ret;
}

redisReply* net::NetRedisCommandArgv(net::NetRedis_t* pNetRedis, const int iTimeOut, int argc, const char** argv)
{
	int _error = redisAppendCommandArgv(pNetRedis->pRedisContext, argc, argv, nullptr);
	if (_error != REDIS_OK)
		return nullptr;
	return NetRedisGetReply(pNetRedis, iTimeOut);
}

bool net::NetRedisCommandNonBlock(NetRedis_t* pNetRedis, const char* format, va_list ap)
{
	if (!NetRedisAddCommand(pNetRedis, format, ap))
		return false;
	return NetRedisWrite(pNetRedis);
}

bool net::NetRedisCommandNonBlock(NetRedis_t* pNetRedis, const char* format, ...)
{
	bool _ret;
	va_list ap;
	va_start(ap, format);
	_ret = NetRedisCommandNonBlock(pNetRedis, format, ap);
	va_end(ap);
	return _ret;
}

bool net::NetRedisAddCommand(NetRedis_t* pNetRedis, const char* format, va_list ap)
{
	if (redisvAppendCommand(pNetRedis->pRedisContext, format, ap) != REDIS_OK)
		return false;
	return true;
}

bool net::NetRedisAddCommand(NetRedis_t* pNetRedis, const char* format, ...)
{
	bool _ret;
	va_list ap;
	va_start(ap, format);
	_ret = NetRedisAddCommand(pNetRedis, format, ap);
	va_end(ap);
	return _ret;
}

bool net::NetRedisWrite(NetRedis_t* pNetRedis)
{
	NetRedisReadAndParse(pNetRedis);
	int _done = 0;
	if (redisBufferWrite(pNetRedis->pRedisContext, &_done) != REDIS_OK)
		return false;
	return true;
}

bool net::NetRedisAuth(net::NetRedis_t* pNetRedis, const char* sPassword)
{
	std::string _command = REDIS_COMMAND_AUTH " ";
	_command += sPassword;
	redisReply* _reply;
	_reply = NetRedisCommand(pNetRedis, DEFAULT_COMMAND_EXECUTION_TIME, _command.c_str());
	if (!_reply)
		return false;
	if (_reply->type == REDIS_REPLY_ERROR)
	{
		if(_reply->str)
			pNetRedis->ErrorMessage = _reply->str;
		freeReplyObject(_reply);
		return false;
	}
	freeReplyObject(_reply);
	// 记录认证密码
	pNetRedis->Password = sPassword;
	return true;
}

bool net::NetRedisPing(net::NetRedis_t* pNetRedis)
{
	redisReply* _reply;
	_reply = NetRedisCommand(pNetRedis, DEFAULT_COMMAND_EXECUTION_TIME, REDIS_COMMAND_PING);
	if (!_reply)
		return false;
	if (_reply->type == REDIS_REPLY_ERROR)
	{
		if (_reply->str)
			pNetRedis->ErrorMessage = _reply->str;
		freeReplyObject(_reply);
		return false;
	}
	freeReplyObject(_reply);
	return true;
}

void net::NetRedisFree(net::NetRedis_t* pNetRedis)
{
	redisFree(pNetRedis->pRedisContext);
	delete pNetRedis;
}

redisReply* net::NetRedisGetReply(net::NetRedis_t* pNetRedis, const int iTimeOut)
{
	int _done = 0;
	int _error = redisBufferWrite(pNetRedis->pRedisContext, &_done);
	if (_error != REDIS_OK)
		return nullptr;
	_error = redisBufferReadWithTimeOut(pNetRedis->pRedisContext, iTimeOut);
	if (_error != REDIS_OK)
		return nullptr;
	redisReply* _ret = nullptr;
	_error = redisGetReplyFromReader(pNetRedis->pRedisContext, (void**)&_ret);
	if (_error != REDIS_OK)
		return nullptr;
	return _ret;
}

void net::NetRedisSetCallBack(net::NetRedis_t* pNetRedis, NetRedis_CallBack cb)
{
	pNetRedis->OtherMsgCallBack = cb;
}

void net::NetRedisReadAndParse(net::NetRedis_t* pNetRedis)
{
	redisBufferReadWithTimeOut(pNetRedis->pRedisContext, 0);
	// 循环解析缓存中的数据
	redisReply* _ret = nullptr;
	while (redisReaderParseSize(pNetRedis->pRedisContext->reader))
	{
		if (redisGetReplyFromReader(pNetRedis->pRedisContext, (void**)&_ret) == REDIS_OK)
		{
			if (pNetRedis->OtherMsgCallBack)
				pNetRedis->OtherMsgCallBack(_ret, pNetRedis);
			freeReplyObject(_ret);
		}
		else {
			break;
		}
	}
}


void NetRedisInit(net::NetRedis_t* pNetRedis)
{
	pNetRedis->Port = 0;
}