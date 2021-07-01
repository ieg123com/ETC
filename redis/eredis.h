/*
Redis常用操作封装成单独类 方便调用
封装为单独类
*/
#pragma once
#include "hiredis2.h"
#include <unordered_map>
#include <unordered_set>
#include <list>

#ifndef CALLBACK_4
#define CALLBACK_4(_object,_class, ...) std::bind(&_object,_class,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4)
#endif

class eredis
{
public:
	
	// 频道名 消息 消息长度 自身指针
	typedef std::function<void(const char* sMsg,const char* cData,const int iLen, eredis* pSelf)> Channel_CallBack;

	void SetPingGap(int64_t time) { m_pingTimeGap_s = time; }
	void SetChannelCallBack(Channel_CallBack cb) { m_ChannelCallBack = cb; }

	net::NetRedis_t* GetNetRedis() { return m_NetRedis; }
	const char* GetErrorMessage()const { return (m_NetRedis)?m_NetRedis->ErrorMessage.c_str():""; }
public:
	// 连接到Redis
	bool ConnectRedis(const std::string& sIp, const int32_t iPort, const std::string& sPassword);
	// 连接非阻塞的Redis
	bool ConnectRedisNonBlock(const std::string& sIp, const int32_t iPort, const std::string& sPassword);
	// 加载lua文件
	bool LoadLuaFile(const std::string& sFileName);

public:
	// 执行命令
	redisReply* RedisCommand(const char* format, ...);
	redisReply* RedisCommand(const int iTimeOut, const char* format, ...);
	// 执行命令 异步
	bool RedisCommandNonBlock(const char* format, ...);
	bool RedisAddCommand(const char* format, ...);
	bool RedisWrite();
	// 执行sha1脚本
	// EvalSha("test.lua", 3000, 0, "%s %s","123","456");
	redisReply* EvalSha(const std::string& sLuaName, const int32_t numkeys, const char* format, ...);
	redisReply* EvalSha(const std::string& sLuaName, const int32_t iTimeOut,const int32_t numkeys, const char* format, ...);
	redisReply* EvalSha(const std::string& sLuaName, const int32_t iTimeOut, const int32_t numkeys, const char* format, va_list ap);
	// 订阅频道 发布与订阅不能同时使用，订阅需重新开启新连接
	bool Subscribe(const std::string& sChannel);
	bool Subscribe(const std::list<std::string>& AllChannel);
	bool Subscribe(const std::list<std::string>& AllChannel, const int32_t iTimeOut);
	// 发布消息
	bool Publish(const std::string& sChannel, const std::string& sWord);
	bool Publish(const std::string& sChannel, const std::string& sWord, const int32_t iTimeOut);
	bool PublishNonBlock(const std::string& sChannel, const std::string& sWord);
	// 退订频道
	bool Unsubscribe(const std::string& sChannel);
	bool Unsubscribe(const std::list<std::string>& AllChannel);
	bool Unsubscribe(const std::list<std::string>& AllChannel, const int32_t iTimeOut);

public:
	void Update();	// 需定时调用
	void Ping();	// 状态维持

private:
	// redis消息到达回调
	void NetRedisCallBack(redisReply* pReply, net::NetRedis_t* pSelf);

	std::string OpenFileWord(const char* sFile);

private:
	net::NetRedis_t		*m_NetRedis;		// redis连接
	int64_t				m_lastPingTime_s;	// 上次ping时间
	int64_t				m_pingTimeGap_s;	// ping间隔
	std::unordered_map<std::string, std::string>	m_luaScript_umap;	// lua脚本
	char				m_buffer[1024];		// 文本缓存
	// 订阅的全部频道
	// 记录 为重连恢复做准备
	std::unordered_set<std::string>	m_SubscribeAllChannel;	

private:
	Channel_CallBack	m_ChannelCallBack;	// 频道消息回调
	// redis连接属性
	std::string			m_Ip;
	int32_t				m_Port;
	std::string			m_Passward;
private:
	const std::string	m_StrMessage = "message";

public:
	eredis();
	~eredis();
};