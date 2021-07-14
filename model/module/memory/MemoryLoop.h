#pragma once
#include <queue>
#include <unordered_map>
#include <functional>
#include "single/ISingleton.h"

namespace Model
{
	/** @brief �ڴ����,����������,��Ҫ���յĶ�����Ҫ�̳������ */
	class MemoryObject
	{
	public:
		virtual void Awake() {};
		virtual void Destory() {};
	};


	/** @brief split �ڴ��,�����������*/
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

		/** @brief ȡ��һ������ */
		template<typename T>
		T* Fetch() {
			// ȡ���Ķ������̳� MemoryObject
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


		/** @brief ���� */
		template<typename T>
		void Recycle(T* obj) {
			// ���յĶ������̳� MemoryObject
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
		// �ڴ��
		std::unordered_map<const type_info*, std::pair<std::queue<MemoryObject*>, std::function<void(MemoryObject*)>>>	m_loop;
	};
}
