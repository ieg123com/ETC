#include "MailBoxComponent.h"
#include "etc/etc.h"
#include "log/log.h"

namespace Model
{
	class MailBoxComponentAwakeSystem : public AwakeSystem<MailBoxComponent>
	{
	public:
		virtual void Awake(const std::shared_ptr<MailBoxComponent>& self) override
		{
			self->Awake();
		}
	};
	REF(MailBoxComponentAwakeSystem, ObjectSystem);


	class MailBoxComponentDestroySystem : public DestroySystem<MailBoxComponent>
	{
	public:
		virtual void Destroy(const std::shared_ptr<MailBoxComponent>& self) override
		{
			self->Destroy();
		}
	};
	REF(MailBoxComponentDestroySystem, ObjectSystem);




	void MailBoxComponent::Awake()
	{
		__StartLoop();
	}

	void MailBoxComponent::Destroy()
	{
		__StopLoop();

		// TODO: 清空未完成的任务队列
		std::function<void()> func;
		while (m_channel.TryPop(func)) {}
	}


	void MailBoxComponent::__StartLoop()
	{
		m_stopped = false;
		go[this]{
			std::function<void()> func;
			while (m_stopped != true)
			{
				m_channel >> func;
				try {
					func();
				}
				catch (std::exception& e)
				{
					LOG_ERROR("内部通信邮箱组件运行任务时出现错误!({})", e.what());
				}
				catch (...)
				{
					LOG_ERROR("内部通信邮箱组件运行任务时出现错误!(未知错误)");
				}
			}


		};
	}

	void MailBoxComponent::__StopLoop()
	{
		m_stopped = true;
		m_channel << std::move([] {});
	}
}