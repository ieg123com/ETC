#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include <functional>
#include "GlobalData.h"


// ÀàÐÍË÷Òý
using TypeIndex = uint32_t;

namespace Model
{
	class TypeFactory;
}

class TypeInfo
{
	friend class Activator;
	friend class Model::TypeFactory;
public:
	const std::string name;
	const std::string raw_name;
	const size_t hash_code;
	const TypeIndex index;

	TypeInfo() :name(""), raw_name(""), hash_code(0), index(Model::GlobalData::GetTypeIndex()) { }
	TypeInfo(const type_info* ty):raw_name(ty->raw_name()),name(ty->name()),hash_code(ty->hash_code()), index(Model::GlobalData::GetTypeIndex()) {}


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

private:
	std::function<void*()>		create_instance;
	std::function<void(void*)>	delete_instance;
};


class Type
{
public:

	TypeInfo* m_info;
	Type() { m_info = nullptr; }
	Type(TypeInfo* info){
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

	bool operator < (const Type& obj)const noexcept {
		if (m_info < obj.m_info)
		{
			return true;
		}
		return false;
	}

	bool operator > (const Type& obj)const noexcept {
		if (m_info > obj.m_info)
		{
			return true;
		}
		return false;
	}

	bool operator <= (const Type& obj)const noexcept {
		if (m_info <= obj.m_info)
		{
			return true;
		}
		return false;
	}

	bool operator >= (const Type& obj)const noexcept {
		if (m_info >= obj.m_info)
		{
			return true;
		}
		return false;
	}

	const char* name()const{
		return m_info->name.c_str();
	}

	const char* class_name()const {
		return m_info->name.c_str()+6;
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

