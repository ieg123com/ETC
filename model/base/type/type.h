#pragma once
#include <memory>
#include <string>
#include <unordered_map>


class TypeInfo
{
public:
	std::string raw_name;
	std::string name;

	bool operator == (const TypeInfo& obj)const noexcept
	{
		if (raw_name == obj.raw_name &&
			name == name)
		{
			return true;
		}
		return false;
	}

	bool operator != (const TypeInfo& obj)const noexcept
	{
		if (raw_name != obj.raw_name ||
			name != obj.name)
		{
			return true;
		}
		return false;
	}
};


class Type
{
public:

	std::shared_ptr<TypeInfo> m_info;
	Type(){}
	Type(std::shared_ptr<TypeInfo> info)
	{
		m_info = info;
	}

	bool operator == (const Type& obj) const noexcept
	{
		if (m_info == obj.m_info)
		{
			return true;
		}
		return false;
	}
	
	bool operator != (const Type& obj)const noexcept
	{
		if (m_info != obj.m_info)
		{
			return true;
		}
		return false;
	}
	
	const char* name()const
	{
		return m_info->name.c_str();
	}

	const char* row_name()const
	{
		return m_info->raw_name.c_str();
	}



};


namespace std
{
	template<>
	struct hash<Type>
	{
		size_t operator()(const Type& self) const noexcept
		{
			if (self.m_info == nullptr)
			{
				return (size_t)0;
			}
			return hash<decltype(self.m_info->name)>()(self.m_info->name) +
				hash<decltype(self.m_info->raw_name)>()(self.m_info->raw_name);
		}
	};
}

namespace Model
{
	class TypeFactory
	{
	public:

		template<typename T>
		std::shared_ptr<TypeInfo> Get()
		{
			auto found = m_all_type_info.find((&typeid(T))->raw_name());
			if (found == m_all_type_info.end())
			{
				auto value = std::make_pair(std::string((&typeid(T))->raw_name()), std::make_shared<TypeInfo>());
				value.second->name = (&typeid(T))->name();
				value.second->raw_name = (&typeid(T))->raw_name();
				found = m_all_type_info.insert(value).first;
			}
			return found->second;
		}

		std::unordered_map<std::string, std::shared_ptr<TypeInfo>>	m_all_type_info;
	};


	extern TypeFactory* g_type_factory;
}




#define typeof(T)  Type(Model::g_type_factory->Get<T>())