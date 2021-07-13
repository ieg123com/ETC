#pragma once
#include <string>
#if _WIN32
#include <windows.h>
#else

#endif


namespace Model
{
	// ���ӿ����ģ��
	class Dll
	{
	public:
		Dll();
		~Dll();

		bool Load(const char* path);

		void* GetAddress(const char* name);

		void Free();

		bool operator()()const noexcept
		{
			return (m_hm == nullptr) ? false : true;
		}
	private:
		HMODULE	m_hm;
		std::string m_path;
	};



}