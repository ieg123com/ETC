#include "OpcodeTypeComponent.h"


OpcodeTypeComponent* OpcodeTypeComponent::Instance = nullptr;

void OpcodeTypeComponent::Awake()
{

}

void OpcodeTypeComponent::Load()
{
	m_opcode_instances.clear();
	m_opcode_types.clear();
	m_opcode_instances.resize(UINT16_MAX + 1);
	m_opcode_types.resize(UINT16_MAX + 1);
	m_type_opcodes.clear();
	m_request_response.clear();
}

void OpcodeTypeComponent::Destroy()
{
	m_opcode_instances.clear();
	m_opcode_types.clear();
	m_type_opcodes.clear();
	m_request_response.clear();
}