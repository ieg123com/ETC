#include "HotfixHelper.h"
#include "helper/dll/DllHelper.h"



namespace Model
{
	Hotfix::Hotfix()
	{
		m_dll = std::make_shared<Dll>();
	}

	Hotfix::~Hotfix()
	{
		Clear();
		m_dll.reset();
	}


	void Hotfix::Load(const char* path)
	{
		if (!(m_dll->Load(path)))
		{
			throw std::exception("�޷����������");
		}
		// �������ӿ�ɹ�
		if (!(m_awake = m_dll->GetAddress("Awake")))
		{
			throw std::exception("ȱʧ��Awake �ⲻ��һ����׼�Ŀ�");
		}
		if (!(m_init = m_dll->GetAddress("Init")))
		{
			throw std::exception("ȱʧ��Init �ⲻ��һ����׼�Ŀ�");
		}
		if (!(m_destroy = m_dll->GetAddress("Destroy")))
		{
			throw std::exception("ȱʧ��Destroy �ⲻ��һ����׼�Ŀ�");
		}

		Awake();

	}

	void Hotfix::Clear()
	{
		if (m_dll)
		{
			Destroy();
			m_dll->Free();
		}
		m_awake = nullptr;
		m_init = nullptr;
		m_destroy = nullptr;
	}

	void Hotfix::Awake()
	{
		((void(*)(void))m_awake)();
	}

	void Hotfix::Init(const stGlobalVar& global)
	{
		((void(*)(const stGlobalVar&))m_init)(global);
	}

	void Hotfix::Destroy()
	{
		((void(*)(void))m_destroy)();
	}

}
