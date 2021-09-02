#pragma once
#include <stdint.h>
#include <functional>
#include <memory>
#include "google/protobuf/message.h"



class stIMessage
{

};

class stIMRequest:
	public stIMessage
{
public:
	int32_t RpcId;
};

class stIMResponse:
	public stIMessage
{
public:
	int32_t RpcId;
	int32_t Error;
	std::string Message;
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


// ��Ϣ�ظ����ú���
using FMReply = std::function<void()>;
// ��Ϣ�ظ����ú���
using FMPReply = std::function<void(PBMessage*)>;
// �ظ���Ϣ����
using FMResponseParse = std::function<std::shared_ptr<PBMessage>(stIMResponse&, const char*, const uint16_t)>;
// ������Ϣ����
using FMRequestParse = std::function<std::shared_ptr<PBMessage>(stIMRequest&, const char*, const uint16_t)>;
// ���ûظ���Ϣ
using FMResetResponse = std::function<bool(PBMessage*,const stIMResponse&)>;