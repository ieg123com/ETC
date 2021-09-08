#pragma once
#include "IMHandler.h"
#include "etc/etc_err.h"



template<typename Request,typename Response>
class AMRpcHandler :
	public IMHandler
{
public:
	static_assert(std::is_base_of<IRequest, Request>::value,
		"The Request type in MRpcHandler needs needs to be inherited from 'IRequest'");
	static_assert(std::is_base_of<IResponse, Response>::value,
		"The Response type in MRpcHandler needs needs to be inherited from 'IResponse'");

	virtual void Handle(const std::shared_ptr<Session>& session, IMessage* message) override
	{
		try
		{
			IRequest* request = dynamic_cast<IRequest*>(message);
			Response response;

			InstanceID instance_id = session->InstanceId();

			std::function<void()> reply = [&] {
				// �Ȼص�����,session�����Ѿ��Ͽ���,������Ҫ�ж�session InstanceID�Ƿ�һ��
				if (session->InstanceId() != instance_id)
				{
					return;
				}
				response.set_rpcid(request->GetRpcId());
					
				session->Reply(&response);
			};

			try {
				Run(session, *(Request*)request, response,reply);
			}
			catch (std::exception& e)
			{
				LOG_ERROR("������Ϣʧ��:{} {}",
					typeof(Request).full_name(),
					e.what());
				response.set_error((int32_t)ETC_ERR::HandleRpcMessageException);
				response.set_message(e.what());
				reply();
			}
			catch (...)
			{
				LOG_ERROR("������Ϣʧ��:{} δ֪����",
					typeof(Request).full_name());
				response.set_error((int32_t)ETC_ERR::HandleRpcMessageException);
				response.set_message("δ֪����");
				reply();
			}
		}
		catch (std::exception& e)
		{
			LOG_ERROR("������Ϣʧ��:{} {}",
				typeof(Request).full_name(),
				e.what());
		}
		catch (...)
		{
			LOG_ERROR("������Ϣʧ��:{} δ֪����",
				typeof(Request).full_name());
		}
	}

	virtual void Run(const std::shared_ptr<Session>& session, Request& request, Response& response, FMReply& reply) = 0;

	virtual const Type GetRequestType() const override { return typeof(Request); }
	virtual const Type GetResponseType() const override { return typeof(Response); }

};
