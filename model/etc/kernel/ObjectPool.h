#pragma once
#include <memory>
#include <queue>
#include <unordered_map>
#include "Object.h"


class ObjectPool
{
public:

	template<typename T>
	std::shared_ptr<T> Fetch() {
		// 取出的对象必须继承 Object
		static_assert(std::is_base_of<Object, T>::value,
			"The fetch object must inherit Object!");
		std::shared_ptr<T> obj;
		auto found = m_pool.find(typeof(T));
		if (found != m_pool.end())
		{
			if (!found->second.empty())
			{
				obj = std::dynamic_pointer_cast<T>(found->second.front());
				found->second.pop();
				obj->RefreshObjectID();
				obj->m_disposed = false;
			}
		}
		if (!obj)
		{
			obj = std::make_shared<T>();
			obj->m_object_type.m_type = typeof(T);
			obj->DebugIncreaseSelf();
		}
		obj->m_is_from_pool = true;
		return obj;
	}

	void Recycle(const std::shared_ptr<Object>& obj) {
		m_pool[obj->m_object_type.m_type].push(obj);
	}


	void clear() {
		m_pool.clear();
	}

	std::string DumpToString() 
	{
		std::string	ctx;
		for (auto& item : m_pool)
		{
			ctx += "[";
			ctx += (item.first.name() + 6);
			ctx += "] (";
			ctx += std::to_string(item.second.size());
			ctx += ")\n";
		}
		return std::move(ctx);
	}

private:

	std::unordered_map<Type, std::queue<std::shared_ptr<Object>>>	m_pool;
};