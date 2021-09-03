#pragma once
#include <stdint.h>
#include <functional>
#include <memory>
#include "other/container/Use.h"
#include "google/protobuf/message.h"



class stIMessage
{

};

class stIMRequest:
	public stIMessage
{
public:
	Use<int32_t> RpcId;
};

class stIMResponse:
	public stIMessage
{
public:
	Use<int32_t> RpcId;
	Use<int32_t> Error;
	Use<std::string> Message;
};

class stIMActorRequest :
	public stIMRequest
{
public:

};


class stIMActorResponse :
	public stIMResponse
{
public:

};




using PBMessage = ::google::protobuf::Message;


// 消息回复调用函数
using FMReply = std::function<void()>;
// 消息回复调用函数
using FMPReply = std::function<void(PBMessage*)>;
// 回复消息解析
using FMResponseParse = std::function<std::shared_ptr<PBMessage>(stIMResponse&, const char*, const uint16_t)>;
// 请求消息解析
using FMRequestParse = std::function<std::shared_ptr<PBMessage>(stIMRequest&, const char*, const uint16_t)>;
// 重置回复消息
using FMResetResponse = std::function<bool(PBMessage*,const stIMResponse&)>;