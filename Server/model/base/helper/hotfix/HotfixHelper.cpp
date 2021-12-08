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
			throw std::exception("无法加载这个库");
		}
		// 加载链接库成功
		if (!(m_awake = m_dll->GetAddress("Awake")))
		{
			throw std::exception("缺失：Awake 这不是一个标准的库");
		}
		if (!(m_init = m_dll->GetAddress("Init")))
		{
			throw std::exception("缺失：Init 这不是一个标准的库");
		}
		if (!(m_destroy = m_dll->GetAddress("Destroy")))
		{
			throw std::exception("缺失：Destroy 这不是一个标准的库");
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
