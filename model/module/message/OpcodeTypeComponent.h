#pragma once
#include "etc/etc.h"
#include "MessageDefines.h"



class OpcodeTypeComponent:
	public Component
{
	std::vector<std::function<PBMessage*(void)>> m_opcode_instances;
	std::vector<Type>	m_opcode_types;
	std::unordered_map<Type, uint16_t>	m_type_opcodes;
	std::unordered_map<Type, Type>	m_request_response;
public:
	static OpcodeTypeComponent* Instance;


	void Awake();

	void Load();

	void Destroy();

	template<typename T>
	void RegisterMessage(const uint16_t msg_id) {
		if (!m_type_opcodes.insert(std::make_pair(typeof(T), msg_id)).second)
		{
			throw std::exception(std::format("消息类型已经注册过了,不能重复注册！type = %s", typeof(T).class_name()).c_str());
		}
		m_opcode_types[msg_id] = typeof(T);
		m_opcode_instances[msg_id] = []()->PBMessage*{ return new T(); };
	}

	void BindRpcMessage(const Type& request, const Type& response) {
		if (!m_request_response.emplace(request, response).second)
		{
			throw std::exception(std::format("已绑定了相同类型的消息。request = %s,response = %s",request.class_name(),response.class_name()).c_str());
		}
	}

	template<typename Request,typename Response>
	void BindRpcMessage() {
		auto found = m_request_response.find(typeof(Request));
		if (found == m_request_response.end())
		{
			m_request_response.emplace(typeof(Request), typeof(Response));
			return;
		}
		if (found->second != typeof(Response))
		{
			throw std::exception(std::format("已绑定了相同类型的消息。request = %s,response = %s", typeof(Request).class_name(), typeof(Response).class_name()).c_str());
		}
	}

	PBMessage* CreateInstanceTry(const uint16_t msg_id)const {
		if (m_opcode_instances[msg_id])
		{
			return m_opcode_instances[msg_id]();
		}
		throw std::exception(std::format("没有注册这个id的消息，msg_id = %u", msg_id).c_str());
	}

	PBMessage* CreateInstanceTry(const Type& tp)const {
		return CreateInstanceTry(GetTypeOpcodeTry(tp));
	}

	uint16_t GetTypeOpcodeTry(const Type& tp)const {
		auto found = m_type_opcodes.find(tp);
		if (found == m_type_opcodes.end())
		{
			throw std::exception(std::format("没有找到类型的消息id，type = %s",tp.class_name()).c_str());
		}
		return found->second;
	}

	


};
