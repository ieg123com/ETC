#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include <functional>
#include "GlobalData.h"
#include "interface/ISupportTypeCreation.h"

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
	std::function<std::shared_ptr<Model::ISupportTypeCreation> ()> create_instance;
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
		constexpr TypeInfo* Get()
		{
			auto found = m_all_type_info.find((&typeid(T))->raw_name());
			if (found == m_all_type_info.end())
			{
				auto value = std::make_pair(std::string((&typeid(T))->raw_name()), new TypeInfo(&typeid(T)));
				if (std::is_base_of<ISupportTypeCreation, T>::value)
				{
					value.second->create_instance = []()->std::shared_ptr<ISupportTypeCreation> {
						//T* new_obj = new T();
						std::shared_ptr<T> obj = std::make_shared<T>();
						//std::shared_ptr<T> obj(new_obj, [](T* self)->void { delete self; });
						return std::reinterpret_pointer_cast<ISupportTypeCreation>(obj);
					};
				}
				else {
					value.second->create_instance = nullptr;
				}
				found = m_all_type_info.insert(value).first;
			}
			return found->second;
		}


		template<typename T>
		static std::shared_ptr<T> CreateInstance(const Type& type)
		{
			if (type.m_info == nullptr)
			{
				return nullptr;
			}
			if (!type.m_info->create_instance)
			{
				return nullptr;
			}
			std::shared_ptr<ISupportTypeCreation> new_obj = type.m_info->create_instance();

			auto event_obj = std::dynamic_pointer_cast<IEventSystem>(new_obj);

			std::shared_ptr<T> ret_obj = std::dynamic_pointer_cast<T>(new_obj);
			if (!ret_obj)
			{
				return nullptr;
			}
			new_obj->BeginInit();
			new_obj->EndInit();
			return ret_obj;
		}
	private:
		std::unordered_map<std::string, TypeInfo*>	m_all_type_info;

	};


	extern TypeFactory* g_type_factory;

}




#define typeof(T)  Type(Model::g_type_factory->Get<T>())