#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include <functional>


// ????????
using TypeIndex = uint32_t;

namespace Model
{
	class TypeFactory;
	class ISupportTypeCreation;
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

	TypeInfo(const TypeIndex idx) :name(""), raw_name(""), hash_code(0), index(idx) { }
	TypeInfo(const type_info* ty,const TypeIndex idx):raw_name(ty->raw_name()),name(ty->name()),hash_code(ty->hash_code()), index(idx) {}


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
	std::function<std::shared_ptr<Model::ISupportTypeCreation>()>		create_instance;
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

	operator bool()const noexcept {
		return (m_info != nullptr);
	}

	Type& operator = (const Type& right) {
		m_info = right.m_info;
		return *this;
	}

	const char* name()const{
		return m_info->name.c_str();
	}

	const char* full_name()const {
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



