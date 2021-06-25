/*
Redis甯哥敤鎿崭綔灏佽鎴愬崟镫被 鏂逛究璋幂敤
灏佽涓哄崟镫被
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
	
	// 棰戦亾鍚?娑堟伅 娑堟伅闀垮害 镊韩鎸囬拡
	typedef std::function<void(const char* sMsg,const char* cData,const int iLen, eredis* pSelf)> Channel_CallBack;

	void SetPingGap(int64_t time) { m_pingTimeGap_s = time; }
	void SetChannelCallBack(Channel_CallBack cb) { m_ChannelCallBack = cb; }

	net::NetRedis_t* GetNetRedis() { return m_NetRedis; }
	const char* GetErrorMessage()const { return (m_NetRedis)?m_NetRedis->ErrorMessage.c_str():""; }
public:
	// 杩炴帴鍒癛edis
	bool ConnectRedis(const std::string& sIp, const int32_t iPort, const std::string& sPassword);
	// 杩炴帴闱为樆濉炵殑Redis
	bool ConnectRedisNonBlock(const std::string& sIp, const int32_t iPort, const std::string& sPassword);
	// 锷犺浇lua鏂囦欢
	bool LoadLuaFile(const std::string& sFileName);

public:
	// 镓ц锻戒护
	redisReply* RedisCommand(const char* format, ...);
	redisReply* RedisCommand(const int iTimeOut, const char* format, ...);
	// 镓ц锻戒护 寮傛
	bool RedisCommandNonBlock(const char* format, ...);
	bool RedisAddCommand(const char* format, ...);
	bool RedisWrite();
	// 镓цsha1鑴氭湰
	// EvalSha("test.lua", 3000, 0, "%s %s","123","456");
	redisReply* EvalSha(const std::string& sLuaName, const int32_t numkeys, const char* format, ...);
	redisReply* EvalSha(const std::string& sLuaName, const int32_t iTimeOut,const int32_t numkeys, const char* format, ...);
	redisReply* EvalSha(const std::string& sLuaName, const int32_t iTimeOut, const int32_t numkeys, const char* format, va_list ap);
	// 璁㈤槄棰戦亾 鍙戝竷涓庤阒呬笉鑳藉悓镞朵娇鐢紝璁㈤槄闇€閲嶆柊寮€鍚柊杩炴帴
	bool Subscribe(const std::string& sChannel);
	bool Subscribe(const std::list<std::string>& AllChannel);
	bool Subscribe(const std::list<std::string>& AllChannel, const int32_t iTimeOut);
	// 鍙戝竷娑堟伅
	bool Publish(const std::string& sChannel, const std::string& sWord);
	bool Publish(const std::string& sChannel, const std::string& sWord, const int32_t iTimeOut);
	bool PublishNonBlock(const std::string& sChannel, const std::string& sWord);
	// 阃€璁㈤阆?
	bool Unsubscribe(const std::string& sChannel);
	bool Unsubscribe(const std::list<std::string>& AllChannel);
	bool Unsubscribe(const std::list<std::string>& AllChannel, const int32_t iTimeOut);

public:
	void Update();	// 闇€瀹氭椂璋幂敤
	void Ping();	// 钟舵€佺淮鎸?

private:
	// redis娑堟伅鍒拌揪锲炶皟
	void NetRedisCallBack(redisReply* pReply, net::NetRedis_t* pSelf);

	std::string OpenFileWord(const char* sFile);

private:
	net::NetRedis_t		*m_NetRedis;		// redis杩炴帴
	int64_t				m_lastPingTime_s;	// 涓婃ping镞堕棿
	int64_t				m_pingTimeGap_s;	// ping闂撮殧
	std::unordered_map<std::string, std::string>	m_luaScript_umap;	// lua鑴氭湰
	char				m_buffer[1024];		// 鏂囨湰缂揿瓨
	// 璁㈤槄镄勫叏閮ㄩ阆?
	// 璁板綍 涓洪吨杩炴仮澶嶅仛鍑嗗
	std::unordered_set<std::string>	m_SubscribeAllChannel;	

private:
	Channel_CallBack	m_ChannelCallBack;	// 棰戦亾娑堟伅锲炶皟
	// redis杩炴帴灞炴€?
	std::string			m_Ip;
	int32_t				m_Port;
	std::string			m_Passward;
private:
	const std::string	m_StrMessage = "message";

public:
	eredis();
	~eredis();
};