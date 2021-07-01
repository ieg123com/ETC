/*
对hiredis.h 异步操作进行封装 方便调用
非线程安全
*/
#pragma once
#include "hiredis/hiredis.h"
#include <functional>
#include <string>
#include <iostream>

#ifndef CALLBACK_2
#define CALLBACK_2(_object,_class, ...) std::bind(&_object,_class,std::placeholders::_1,std::placeholders::_2)
#endif

// redis 命令
#define REDIS_COMMAND_AUTH	"AUTH"		// 认证
#define REDIS_COMMAND_PING	"PING"		// ping
#define REDIS_COMMAND_SCRIPT_LOAD	"SCRIPT LOAD"	// 脚本加载
#define REDIS_COMMAND_EVALSHA		"EVALSHA"		// 执行指定sha脚本
#define REDIS_COMMAND_SUBSCRIBE		"SUBSCRIBE"		// 订阅频道
#define REDIS_COMMAND_UNSUBSCRIBE	"UNSUBSCRIBE"	// 退订频道
#define REDIS_COMMAND_PUBLISH		"PUBLISH"		// 发布消息到频道


#define DEFAULT_COMMAND_EXECUTION_TIME	3000	// 默认命令执行时间 3秒


namespace net
{
	typedef std::function<void(redisReply*, struct NetRedis_t*)> NetRedis_CallBack;
	struct NetRedis_t
	{
		redisContext* pRedisContext;
		NetRedis_CallBack	OtherMsgCallBack;	// 其他消息到达通知 如订阅消息
		std::string		Ip;						// 地址
		int32_t			Port;					// 端口
		std::string		Password;				// 密码
		std::string		ErrorMessage;			// 错误信息
	};


	// 连接
	NetRedis_t* NetRedisConnectNonBlock(const char* sIp, const int iPort, const int iTimeOut);
	bool NetRedisReconnect(NetRedis_t* pNetRdis);
	// 命令
	redisReply* NetRedisCommand(NetRedis_t* pNetRedis, const int iTimeOut, const char* format, va_list ap);
	redisReply* NetRedisCommand(NetRedis_t* pNetRedis, const int iTimeOut, const char* format, ...);
	redisReply* NetRedisCommandArgv(NetRedis_t* pNetRedis, const int iTimeOut, int argc, const char** argv);
	bool NetRedisCommandNonBlock(NetRedis_t* pNetRedis, const char* format, va_list ap);
	bool NetRedisCommandNonBlock(NetRedis_t* pNetRedis, const char* format, ...);
	bool NetRedisAddCommand(NetRedis_t* pNetRedis, const char* format, va_list ap);
	bool NetRedisAddCommand(NetRedis_t* pNetRedis, const char* format, ...);
	bool NetRedisWrite(NetRedis_t* pNetRedis);

	// 认证 持久
	bool NetRedisAuth(NetRedis_t* pNetRedis, const char* sPassword);
	bool NetRedisPing(NetRedis_t* pNetRedis);
	void NetRedisFree(NetRedis_t* pNetRedis);

	redisReply* NetRedisGetReply(NetRedis_t* pNetRedis, const int iTimeOut);
	// 设置回调
	void NetRedisSetCallBack(NetRedis_t* pNetRedis, NetRedis_CallBack cb);

	// 读取并解析rdis中的数据
	// 将此函数放入主循环中调用
	void NetRedisReadAndParse(NetRedis_t* pNetRedis);




}

