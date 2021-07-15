#pragma once
#include <memory>
#include <string>
#include <unordered_map>


class TypeInfo
{
public:
	const std::string name;
	const std::string raw_name;
	const size_t hash_code;

	TypeInfo():name(""),raw_name(""),hash_code(0) {}
	TypeInfo(const type_info* ty):raw_name(ty->raw_name()),name(ty->name()),hash_code(ty->hash_code()){}


	bool operator == (const TypeInfo& obj)const noexcept{
		if (raw_name == obj.raw_name)
		{
			return true;
		}
		return false;
	}

	bool operator != (const TypeInfo& obj)const noexcept{
		if (raw_name != obj.raw_name)
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
	Type(std::shared_ptr<TypeInfo> info){
		m_info = info;
	}

	bool operator == (const Type& obj) const noexcept{
		if (m_info == obj.m_info)
		{
			return true;
		}
		return false;
	}
	
	bool operator != (const Type& obj)const noexcept{
		if (m_info != obj.m_info)
		{
			return true;
		}
		return false;
	}
	
	const char* name()const{
		return m_info->name.c_str();
	}

	const char* row_name()const{
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
			return self.m_info->hash_code;
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
				auto value = std::make_pair(std::string((&typeid(T))->raw_name()), std::make_shared<TypeInfo>(&typeid(T)));
				found = m_all_type_info.insert(value).first;
			}
			return found->second;
		}

		std::unordered_map<std::string, std::shared_ptr<TypeInfo>>	m_all_type_info;
	};


	extern TypeFactory* g_type_factory;
}




#define typeof(T)  Type(Model::g_type_factory->Get<T>())