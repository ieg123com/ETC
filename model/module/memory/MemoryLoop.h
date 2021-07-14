#pragma once
#include <queue>
#include <unordered_map>
#include <functional>
#include "single/ISingleton.h"

namespace Model
{
	/** @brief 内存对象,轻量级对象,需要回收的对象，需要继承这个类 */
	class MemoryObject
	{
	public:
		virtual void Awake() {};
		virtual void Destory() {};
	};


	/** @brief split 内存池,轻量级对象池*/
	class MemoryLoop :
		public ISingleton<MemoryLoop>
	{
	public:
		static MemoryLoop& Instance() {
			static MemoryLoop data_loop;
			return data_loop;
		}

		~MemoryLoop() {
			Clear();
		}

		/** @brief 取出一个对象 */
		template<typename T>
		T* Fetch() {
			// 取出的对象必须继承 MemoryObject
			static_assert(std::is_base_of<MemoryObject, T>::value,
				"The fetch object must inherit MemoryObject!");
			T* obj = nullptr;
			auto found = m_loop.find(&typeid(T));
			if (found != m_loop.end())
			{
				if (!found->second.first.empty())
				{
					obj = static_cast<T*>(found->second.first.front());
					found->second.first.pop();
				}
			}
			if (obj == nullptr)
			{
				obj = new T();
			}

			obj->Awake();
			return obj;
		}


		/** @brief 回收 */
		template<typename T>
		void Recycle(T* obj) {
			// 回收的对象必须继承 MemoryObject
			static_assert(std::is_base_of<MemoryObject, T>::value,
				"The recycle object must inherit MemoryObject!");

			obj->Destory();

			auto found = m_loop.find(&typeid(T));
			if (found == m_loop.end())
			{
				found = m_loop.insert(std::make_pair(&typeid(T), std::make_pair(std::queue<MemoryObject*>(), [](MemoryObject* obj) -> void { delete (T*)obj; }))).first;
			}
			found->second.first.push(obj);
		}

		void Clear() {
			for (auto& item : m_loop)
			{
				auto& loop = item.second.first;
				auto& del = item.second.second;
				while (!loop.empty())
				{
					MemoryObject* obj = loop.front();
					loop.pop();
					del(obj);
				}
			}
			m_loop.clear();
		}

		template<typename T>
		size_t Count() {
			static_assert(std::is_base_of<MemoryObject, T>::value,
				"The count type must inherit MemoryObject!");
			auto found = m_loop.find(&typeid(T));
			if (found == m_loop.end())
			{
				return 0;
			}
			return found->second.first.size();
		}

	private:
		// 内存池
		std::unordered_map<const type_info*, std::pair<std::queue<MemoryObject*>, std::function<void(MemoryObject*)>>>	m_loop;
	};
}
