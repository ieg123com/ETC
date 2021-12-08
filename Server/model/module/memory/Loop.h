#pragma once
#include <queue>
#include <string>
#include <memory>
#include "single/ISingleton.h"


namespace Model
{
	template<typename T>
	class Loop :
		public ISingleton<Loop<T>>
	{
		std::queue<T*>	m_loop;
	public:

		std::shared_ptr<T> Fetch() {
			T* data;
			if (m_loop.empty())
			{
				data = new T();
			}
			else {
				data = m_loop.front();
				m_loop.pop();
			}
			return std::shared_ptr<T>(data, [this](T* self)->void {this->Recycle(self); });
		}

		void Recycle(T* data) {
			m_loop.emplace(data);
		}
	};

}
