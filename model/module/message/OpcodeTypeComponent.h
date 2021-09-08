#pragma once
#include "etc/etc.h"



class OpcodeTypeComponent:
	public Component
{

	std::vector<Type>	m_opcode_types;
	std::unordered_map<Type, uint16_t>	m_type_opcodes;
	std::unordered_map<Type, Type>	m_type_request_response;
	std::vector<uint16_t>			m_opcode_request_response;


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


	// 用协议码创建消息实例
	std::shared_ptr<IMessage> CreateInstanceTry(const uint16_t opcode)const;

	// 用请求消息的协议码，创建一条回复的消息实例
	std::shared_ptr<IMessage> CreateResponseInstanceTry(const uint16_t opcode);


	template<typename T>
	static std::shared_ptr<T> CreateInstanceTry(const uint16_t opcode) {
		auto message = OpcodeTypeComponent::Instance->CreateInstanceTry(opcode);
		if (auto response = std::dynamic_pointer_cast<T>(message))
		{
			return response;
		}
		throw std::exception(
			std::format("无法转换类型 %s => %s,opcode = %d", 
				message->GetType().full_name(),
				typeof(T).full_name(),
				opcode).c_str());
	}

	template<typename T>
	static std::shared_ptr<T> CreateResponseInstanceTry(const uint16_t opcode) {
		auto message = OpcodeTypeComponent::Instance->CreateResponseInstanceTry(opcode);
		if (auto response = std::dynamic_pointer_cast<T>(message))
		{
			return response;
		}
		throw std::exception(
			std::format(
				"无法转换类型 %s => %s,opcode = %d", 
				message->GetType().full_name(), 
				typeof(T).full_name(), opcode).c_str());
	}

	
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