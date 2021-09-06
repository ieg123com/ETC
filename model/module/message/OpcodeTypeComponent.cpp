#include "OpcodeTypeComponent.h"


OpcodeTypeComponent* OpcodeTypeComponent::Instance = nullptr;

void OpcodeTypeComponent::Awake()
{

}

void OpcodeTypeComponent::Load()
{
	m_opcode_types.clear();
	m_opcode_types.resize(UINT16_MAX + 1);
	m_type_opcodes.clear();
	m_type_request_response.clear();
	m_opcode_request_response.resize(UINT16_MAX + 1);
	m_opcode_msg_types.resize(UINT16_MAX + 1);
	memset(m_opcode_request_response.data(), 0, sizeof(*m_opcode_request_response.data()) * m_opcode_request_response.size());
}

void OpcodeTypeComponent::Destroy()
{
	m_opcode_types.clear();
	m_type_opcodes.clear();
	m_type_request_response.clear();
	m_opcode_request_response.clear();
	m_opcode_msg_types.size();
}

void OpcodeTypeComponent::__RegisterMessage(const Type& tp, const uint16_t opcode, const EMessageType msg_type)
{
	if (!m_type_opcodes.emplace(tp, opcode).second)
	{
		throw std::exception(std::format("消息类型已经注册过了,不能重复注册！type = %s", tp.full_name()).c_str());
	}
	m_opcode_types[opcode] = tp;
	m_opcode_msg_types[opcode] = msg_type;
}

void OpcodeTypeComponent::__BindRpcMessage(const Type& request, const Type& response)
{
	if (!m_type_request_response.emplace(request, response).second)
	{
		throw std::exception(std::format("已绑定了相同类型的消息。request = %s,response = %s", request.full_name(), response.full_name()).c_str());
	}
}




std::shared_ptr<IMessage> OpcodeTypeComponent::CreateInstanceTry(const uint16_t msg_id)const
{
	if (m_opcode_types[msg_id])
	{
		return TypeFactory::CreateInstance<IMessage>(m_opcode_types[msg_id]);
	}
	throw std::exception(std::format("没有注册这个id的消息，msg_id = %u", msg_id).c_str());
}

std::shared_ptr<IMessage> OpcodeTypeComponent::CreateResponseInstanceTry(const uint16_t opcode)
{
	return CreateInstanceTry(GetResponseOpcodeTry(opcode));
}


