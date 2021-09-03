#pragma once
#include "etc/etc.h"
#include "interface/IMessage.h"



class OpcodeTypeComponent:
	public Component
{
	std::vector<std::function<std::shared_ptr<PBMessage>(void)>> m_opcode_instances;

	std::unordered_map<Type, FMRequestParse>	m_type_request_parse;
	std::unordered_map<Type, FMResponseParse>	m_type_response_parse;
	std::unordered_map<Type, FMResetResponse>	m_type_reset_response;
	std::vector<FMRequestParse>		m_opcode_request_parse;
	std::vector<FMResponseParse>	m_opcode_response_parse;
	std::vector<FMResetResponse>	m_opcode_reset_response;

	
	std::vector<Type>	m_opcode_types;
	std::unordered_map<Type, uint16_t>	m_type_opcodes;
	std::unordered_map<Type, Type>	m_type_request_response;
	std::vector<uint16_t>			m_opcode_request_response;
public:
	static OpcodeTypeComponent* Instance;


	void Awake();

	void Load();

	void Destroy();

	template<typename T>
	void RegisterMessage(const uint16_t msg_id) {
		if (!m_type_opcodes.emplace(typeof(T), msg_id).second)
		{
			throw std::exception(std::format("消息类型已经注册过了,不能重复注册！type = %s", typeof(T).full_name()).c_str());
		}
		m_opcode_types[msg_id] = typeof(T);
		m_opcode_instances[msg_id] = []()->std::shared_ptr<PBMessage>{ return std::make_shared<T>(); };
	}

	void RegisterRequestParse(const Type& tp, FMRequestParse& parse_req) {
		m_type_request_parse.emplace(tp, parse_req);
	}

	void RegisterResponseParse(const Type& tp, FMResponseParse& parse_rpo) {
		m_type_response_parse.emplace(tp, parse_rpo);
	}

	void RegisterResetResponse(const Type& tp, FMResetResponse& reset_rpo) {
		m_type_reset_response.emplace(tp, reset_rpo);
	}

	void BindRpcMessage(const Type& request, const Type& response) {
		if (!m_type_request_response.emplace(request, response).second)
		{
			throw std::exception(std::format("已绑定了相同类型的消息。request = %s,response = %s",request.full_name(),response.full_name()).c_str());
		}
	}

	template<typename Request,typename Response>
	void BindRpcMessage() {
		auto found = m_type_request_response.find(typeof(Request));
		if (found == m_type_request_response.end())
		{
			m_type_request_response.emplace(typeof(Request), typeof(Response));
			RegisterRequestParse(typeof(Request), MRequestParse<Request>()());
			RegisterResponseParse(typeof(Response), MResponseParse<Response>()());
			RegisterResetResponse(typeof(Response), MResetResponse<Response>()());
			return;
		}
		if (found->second != typeof(Response))
		{
			throw std::exception(std::format("已绑定了相同类型的消息。request = %s,response = %s", typeof(Request).full_name(), typeof(Response).full_name()).c_str());
		}
	}

	std::shared_ptr<PBMessage> CreateInstanceTry(const uint16_t msg_id)const {
		if (m_opcode_instances[msg_id])
		{
			return m_opcode_instances[msg_id]();
		}
		throw std::exception(std::format("没有注册这个id的消息，msg_id = %u", msg_id).c_str());
	}

	std::shared_ptr<PBMessage> CreateInstanceTry(const Type& tp)const {
		return CreateInstanceTry(GetTypeOpcodeTry(tp));
	}

	std::shared_ptr<PBMessage> CreateResponseInstanceTry(const uint16_t opcode);

	
	// 获取消息id
	uint16_t GetTypeOpcodeTry(const Type& tp)const {
		auto found = m_type_opcodes.find(tp);
		if (found == m_type_opcodes.end())
		{
			throw std::exception(std::format("没有找到类型的消息id，type = %s",tp.full_name()).c_str());
		}
		return found->second;
	}

	// 获取消息类型
	Type GetOpcodeTypeTry(const int16_t opcode);

	// 获取回复消息类型
	Type GetResponseTypeTry(const Type& tp);

	// 获取回复消息id
	uint16_t GetResponseOpcodeTry(const int16_t opcode);



	std::shared_ptr<PBMessage> RequestMessageParse(const uint16_t opcode, stIMRequest& strequest, const char* data, const uint16_t len);

	std::shared_ptr<PBMessage> ResponseMessageParse(const uint16_t opcode, stIMResponse& stresponse, const char* data, const uint16_t len);

	bool ResetMessageResponse(const uint16_t opcode, PBMessage* response, const stIMResponse& stresponse);
};
