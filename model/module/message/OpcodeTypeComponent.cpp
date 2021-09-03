#include "OpcodeTypeComponent.h"


OpcodeTypeComponent* OpcodeTypeComponent::Instance = nullptr;

void OpcodeTypeComponent::Awake()
{

}

void OpcodeTypeComponent::Load()
{
	m_opcode_instances.clear();
	m_type_request_parse.clear();
	m_type_response_parse.clear();
	m_type_reset_response.clear();
	m_opcode_request_parse.reserve(UINT16_MAX + 1);
	m_opcode_response_parse.reserve(UINT16_MAX + 1);
	m_opcode_reset_response.reserve(UINT16_MAX + 1);
	m_opcode_types.clear();
	m_opcode_instances.resize(UINT16_MAX + 1);
	m_opcode_types.resize(UINT16_MAX + 1);
	m_type_opcodes.clear();
	m_type_request_response.clear();
	m_opcode_request_response.resize(UINT16_MAX + 1);
	memset(m_opcode_request_response.data(), 0, sizeof(*m_opcode_request_response.data()) * m_opcode_request_response.size());
}

void OpcodeTypeComponent::Destroy()
{
	m_opcode_instances.clear();
	m_type_request_parse.clear();
	m_type_response_parse.clear();
	m_type_reset_response.clear();
	m_opcode_request_parse.clear();
	m_opcode_response_parse.clear();
	m_opcode_reset_response.clear();
	m_opcode_types.clear();
	m_type_opcodes.clear();
	m_type_request_response.clear();
	m_opcode_request_response.clear();
}

std::shared_ptr<PBMessage> OpcodeTypeComponent::CreateResponseInstanceTry(const uint16_t opcode)
{
	return CreateInstanceTry(GetResponseOpcodeTry(opcode));
}

Type OpcodeTypeComponent::GetOpcodeTypeTry(const int16_t opcode)
{
	if (m_opcode_types[opcode])
	{
		return m_opcode_types[opcode];
	}
	throw std::exception(std::format("没有知道这消息id的类型,opcode = %u", opcode).c_str());
}

Type OpcodeTypeComponent::GetResponseTypeTry(const Type& tp)
{
	auto found = m_type_request_response.find(tp);
	if (found == m_type_request_response.end())
	{
		std::exception(std::format("没有通过类型找到回复类型,type = %s", tp.full_name()).c_str());
	}
	return found->second;
}

uint16_t OpcodeTypeComponent::GetResponseOpcodeTry(const int16_t opcode)
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

std::shared_ptr<PBMessage> OpcodeTypeComponent::RequestMessageParse(const uint16_t opcode, stIMRequest& strequest, const char* data, const uint16_t len)
{
	if (m_opcode_request_parse[opcode])
	{
		return m_opcode_request_parse[opcode](strequest, data, len);
	}
	if (m_opcode_types[opcode])
	{
		auto found = m_type_request_parse.find(m_opcode_types[opcode]);
		if (found == m_type_request_parse.end())return nullptr;
		m_opcode_request_parse[opcode] = found->second;
		return found->second(strequest, data, len);
	}
	return nullptr;
}

std::shared_ptr<PBMessage> OpcodeTypeComponent::ResponseMessageParse(const uint16_t opcode, stIMResponse& stresponse, const char* data, const uint16_t len)
{
	if (m_opcode_response_parse[opcode])
	{
		return m_opcode_response_parse[opcode](stresponse, data, len);
	}
	if (m_opcode_types[opcode])
	{
		auto found = m_type_response_parse.find(m_opcode_types[opcode]);
		if (found == m_type_response_parse.end())return nullptr;
		m_opcode_response_parse[opcode] = found->second;
		return found->second(stresponse, data, len);
	}
	return nullptr;
}

bool OpcodeTypeComponent::ResetMessageResponse(const uint16_t opcode,PBMessage* response, const stIMResponse& stresponse)
{
	if (m_opcode_reset_response[opcode])
	{
		return m_opcode_reset_response[opcode](response, stresponse);
	}
	if (m_opcode_types[opcode])
	{
		auto found = m_type_reset_response.find(m_opcode_types[opcode]);
		if (found == m_type_reset_response.end())return false;
		m_opcode_reset_response[opcode] = found->second;
		return found->second(response, stresponse);
	}
	return false;
}
