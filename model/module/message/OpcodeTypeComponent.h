#pragma once
#include "etc/etc.h"
#include "interface/IMessage.h"



class OpcodeTypeComponent:
	public Component
{

	std::vector<Type>	m_opcode_types;
	std::unordered_map<Type, uint16_t>	m_type_opcodes;
	std::unordered_map<Type, Type>	m_type_request_response;
	std::vector<uint16_t>			m_opcode_request_response;

	// 用来记录外网消息的，== 1 为外网消息
	std::vector<uint8_t>	m_outer_opcode;

	std::vector<EMessageType>	m_opcode_msg_types;

public:
	static OpcodeTypeComponent* Instance;


	void Awake();

	void Load();

	void Destroy();

	// 注册消息，为消息协议设置协议码
	void __RegisterMessage(const Type& tp, const uint16_t opcode,const EMessageType msg_type);

	// 绑定rpc消息
	void __BindRpcMessage(const Type& request, const Type& response);

	// 将一条消息注册为外网消息
	void __RegisterOuterMessage(const uint16_t opcode);

	// 是外网消息
	bool IsOuterMessage(const uint16_t opcode)const;
	bool IsOuterMessage(const Type& tp)const;

	// 用协议码创建消息实例
	std::shared_ptr<IMessage> CreateInstanceTry(const uint16_t opcode)const;

	// 用请求消息的协议码，创建一条回复的消息实例
	std::shared_ptr<IMessage> CreateResponseInstanceTry(const uint16_t opcode);

	
	// 获取消息id
	uint16_t GetTypeOpcodeTry(const Type& tp)const;

	// 获取消息类型
	Type GetOpcodeTypeTry(const int16_t opcode)const;

	// 获取回复消息类型
	Type GetResponseTypeTry(const Type& tp)const;

	// 获取回复消息id
	uint16_t GetResponseOpcodeTry(const int16_t opcode);

	EMessageType GetMessageType(const int16_t opcode);
};











inline bool OpcodeTypeComponent::IsOuterMessage(const uint16_t opcode)const
{
	return (m_outer_opcode[opcode] == 1);
}

inline bool OpcodeTypeComponent::IsOuterMessage(const Type& tp)const
{
	uint16_t opcode = 0;
	try
	{
		opcode = GetOpcodeTypeTry(tp);
	}
	catch (...)
	{
		return false;
	};
	return IsOuterMessage(opcode);
}

inline uint16_t OpcodeTypeComponent::GetTypeOpcodeTry(const Type& tp)const
{
	auto found = m_type_opcodes.find(tp);
	if (found == m_type_opcodes.end())
	{
		throw std::exception(std::format("没有找到类型的消息id，type = %s", tp.full_name()).c_str());
	}
	return found->second;
}

inline Type OpcodeTypeComponent::GetOpcodeTypeTry(const int16_t opcode)const
{
	if (m_opcode_types[opcode])
	{
		return m_opcode_types[opcode];
	}
	throw std::exception(std::format("没有知道这消息id的类型,opcode = %u", opcode).c_str());
}

inline Type OpcodeTypeComponent::GetResponseTypeTry(const Type& tp)const
{
	auto found = m_type_request_response.find(tp);
	if (found == m_type_request_response.end())
	{
		std::exception(std::format("没有通过类型找到回复类型,type = %s", tp.full_name()).c_str());
	}
	return found->second;
}

inline uint16_t OpcodeTypeComponent::GetResponseOpcodeTry(const int16_t opcode)
{
	if (m_opcode_request_response[opcode] != 0)
	{
		return m_opcode_request_response[opcode];
	}
	Type response_type = GetResponseTypeTry(GetOpcodeTypeTry(opcode));
	uint16_t response_opcode = GetTypeOpcodeTry(response_type);
	m_opcode_request_response[opcode] = response_opcode;
	return response_opcode;
}

inline EMessageType OpcodeTypeComponent::GetMessageType(const int16_t opcode)
{
	return m_opcode_msg_types[opcode];
}