#pragma once
#include <stdint.h>
#include <functional>
#include <memory>
#include <string>
#include "google/protobuf/message.h"
#include "MessageType.h"
#include "interface/ISupportTypeCreation.h"
#include "model/base/type/type.h"
#include "model/module/other/MessageType.h"

#undef GetMessage



// 消息协议接口
class IMessage :public ::google::protobuf::Message, public Model::ISupportTypeCreation 
{
public:
	virtual Type GetType()const = 0;
	virtual uint16_t GetOpcode()const = 0;
	virtual EMessageType GetMessageType()const = 0;
};

class IRequest :public ::IMessage
{
public:
	virtual int32_t GetRpcId()const = 0;
	virtual void SetRpcId(const int32_t val) = 0;
};

class IResponse :public ::IMessage
{
public:
	virtual int32_t GetRpcId()const = 0;
	virtual void SetRpcId(const int32_t val) = 0;
	virtual int32_t GetError()const = 0;
	virtual void SetError(const int32_t val) = 0;
	virtual const ::std::string& GetMessage()const = 0;
	virtual void SetMessage(const ::std::string& val) = 0;
};

class IActorMessage : public IMessage
{
public:
	virtual int32_t GetRpcId()const = 0;
	virtual void SetRpcId(const int32_t val) = 0;
};

class IActorRequest : public IRequest {};

class IActorResponse : public IResponse {};

class IActorLocationMessage :public IActorRequest {};

class IActorLocationRequest :public IActorRequest{};

class IActorLocationResponse :public IActorResponse{};



// 消息回复调用函数
using FMReply = std::function<void()>;
// 消息回复调用函数
using FMPReply = std::function<void(IResponse*)>;