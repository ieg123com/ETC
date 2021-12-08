#include "DllHelper.h"
#include <stdio.h>
#include <string>

namespace Model
{
	Dll::Dll()
	{
		m_hm = nullptr;
	}

	Dll::~Dll()
	{
		Free();
	}

	bool Dll::Load(const char* path)
	{
		if (m_hm)
		{
			throw std::exception(std::string("已经加载过动态链接库!(" + m_path + ")").c_str());
		}
		m_hm = LoadLibrary(path);
		m_path = path;
		return m_hm;
	}


	void* Dll::GetAddress(const char* name)
	{
		if (m_hm == nullptr)
		{
			return nullptr;
		}
		return GetProcAddress(m_hm, name);
	}

	void Dll::Free()
	{
		if (m_hm)
		{
			FreeLibrary(m_hm);
		}
		m_path = "";
	}
}