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

	// ע����Ϣ��Ϊ��ϢЭ������Э����
	void __RegisterMessage(const Type& tp, const uint16_t opcode,const EMessageType msg_type);

	// ��rpc��Ϣ
	void __BindRpcMessage(const Type& request, const Type& response);


	// ��Э���봴����Ϣʵ��
	std::shared_ptr<IMessage> CreateInstanceTry(const uint16_t opcode)const;

	// ��������Ϣ��Э���룬����һ���ظ�����Ϣʵ��
	std::shared_ptr<IMessage> CreateResponseInstanceTry(const uint16_t opcode);


	template<typename T>
	static std::shared_ptr<T> CreateInstanceTry(const uint16_t opcode) {
		auto message = OpcodeTypeComponent::Instance->CreateInstanceTry(opcode);
		if (auto response = std::dynamic_pointer_cast<T>(message))
		{
			return response;
		}
		throw std::exception(
			std::format("�޷�ת������ %s => %s,opcode = %d", 
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
				"�޷�ת������ %s => %s,opcode = %d", 
				message->GetType().full_name(), 
				typeof(T).full_name(), opcode).c_str());
	}

	
	// ��ȡ��Ϣid
	uint16_t GetTypeOpcodeTry(const Type& tp)const;

	// ��ȡ��Ϣ����
	Type GetOpcodeTypeTry(const int16_t opcode)const;

	// ��ȡ�ظ���Ϣ����
	Type GetResponseTypeTry(const Type& tp)const;

	// ��ȡ�ظ���Ϣid
	uint16_t GetResponseOpcodeTry(const int16_t opcode);

	EMessageType GetMessageType(const int16_t opcode);
};











inline uint16_t OpcodeTypeComponent::GetTypeOpcodeTry(const Type& tp)const
{
	auto found = m_type_opcodes.find(tp);
	if (found == m_type_opcodes.end())
	{
		throw std::exception(std::format("û���ҵ����͵���Ϣid��type = %s", tp.full_name()).c_str());
	}
	return found->second;
}

inline Type OpcodeTypeComponent::GetOpcodeTypeTry(const int16_t opcode)const
{
	if (m_opcode_types[opcode])
	{
		return m_opcode_types[opcode];
	}
	throw std::exception(std::format("û��֪������Ϣid������,opcode = %u", opcode).c_str());
}

inline Type OpcodeTypeComponent::GetResponseTypeTry(const Type& tp)const
{
	auto found = m_type_request_response.find(tp);
	if (found == m_type_request_response.end())
	{
		std::exception(std::format("û��ͨ�������ҵ��ظ�����,type = %s", tp.full_name()).c_str());
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