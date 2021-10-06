#pragma once
#include <queue>
#include <string>
#include <memory>
#include "single/ISingleton.h"


namespace Model
{

	class StringLoop:
		public ISingleton<StringLoop>
	{
		std::queue<std::string*>	m_str_loop;
	public:

		std::shared_ptr<std::string> Fetch() {
			std::string* data;
			if (m_str_loop.empty())
			{
				data = new std::string();
			}
			else {
				data = m_str_loop.front();
				m_str_loop.pop();
			}
			return std::shared_ptr<std::string>(data, [this](std::string* self)->void{this->Recycle(self); });
		}

		void Recycle(std::string* data) {
			m_str_loop.emplace(data);
		}
	};

}