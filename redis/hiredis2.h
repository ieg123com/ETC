/*
瀵筯iredis.h 寮傛鎿崭綔杩涜灏佽 鏂逛究璋幂敤
闱炵嚎绋嫔畨鍏?
*/
#pragma once
#include "hiredis/hiredis.h"
#include <functional>
#include <string>
#include <iostream>

#ifndef CALLBACK_2
#define CALLBACK_2(_object,_class, ...) std::bind(&_object,_class,std::placeholders::_1,std::placeholders::_2)
#endif

// redis 锻戒护
#define REDIS_COMMAND_AUTH	"AUTH"		// 璁よ瘉
#define REDIS_COMMAND_PING	"PING"		// ping
#define REDIS_COMMAND_SCRIPT_LOAD	"SCRIPT LOAD"	// 鑴氭湰锷犺浇
#define REDIS_COMMAND_EVALSHA		"EVALSHA"		// 镓ц鎸囧畾sha鑴氭湰
#define REDIS_COMMAND_SUBSCRIBE		"SUBSCRIBE"		// 璁㈤槄棰戦亾
#define REDIS_COMMAND_UNSUBSCRIBE	"UNSUBSCRIBE"	// 阃€璁㈤阆?
#define REDIS_COMMAND_PUBLISH		"PUBLISH"		// 鍙戝竷娑堟伅鍒伴阆?


#define DEFAULT_COMMAND_EXECUTION_TIME	3000	// 榛樿锻戒护镓ц镞堕棿 3绉?


namespace net
{
	typedef std::function<void(redisReply*, struct NetRedis_t*)> NetRedis_CallBack;
	struct NetRedis_t
	{
		redisContext* pRedisContext;
		NetRedis_CallBack	OtherMsgCallBack;	// 鍏朵粬娑堟伅鍒拌揪阃氱煡 濡傝阒呮秷鎭?
		std::string		Ip;						// 鍦板潃
		int32_t			Port;					// 绔彛
		std::string		Password;				// 瀵嗙爜
		std::string		ErrorMessage;			// 阌栾淇℃伅
	};


	// 杩炴帴
	NetRedis_t* NetRedisConnectNonBlock(const char* sIp, const int iPort, const int iTimeOut);
	bool NetRedisReconnect(NetRedis_t* pNetRdis);
	// 锻戒护
	redisReply* NetRedisCommand(NetRedis_t* pNetRedis, const int iTimeOut, const char* format, va_list ap);
	redisReply* NetRedisCommand(NetRedis_t* pNetRedis, const int iTimeOut, const char* format, ...);
	redisReply* NetRedisCommandArgv(NetRedis_t* pNetRedis, const int iTimeOut, int argc, const char** argv);
	bool NetRedisCommandNonBlock(NetRedis_t* pNetRedis, const char* format, va_list ap);
	bool NetRedisCommandNonBlock(NetRedis_t* pNetRedis, const char* format, ...);
	bool NetRedisAddCommand(NetRedis_t* pNetRedis, const char* format, va_list ap);
	bool NetRedisAddCommand(NetRedis_t* pNetRedis, const char* format, ...);
	bool NetRedisWrite(NetRedis_t* pNetRedis);

	// 璁よ瘉 鎸佷箙
	bool NetRedisAuth(NetRedis_t* pNetRedis, const char* sPassword);
	bool NetRedisPing(NetRedis_t* pNetRedis);
	void NetRedisFree(NetRedis_t* pNetRedis);

	redisReply* NetRedisGetReply(NetRedis_t* pNetRedis, const int iTimeOut);
	// 璁剧疆锲炶皟
	void NetRedisSetCallBack(NetRedis_t* pNetRedis, NetRedis_CallBack cb);

	// 璇诲彇骞惰В鏋恟dis涓殑鏁版嵁
	// 灏嗘鍑芥暟鏀惧叆涓诲惊鐜腑璋幂敤
	void NetRedisReadAndParse(NetRedis_t* pNetRedis);




}

