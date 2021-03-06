#pragma once
#include "type.h"
#include "interface/ISupportTypeCreation.h"
#include "GlobalData.h"



namespace Model
{

	extern class TypeFactory* g_type_factory;

	class TypeFactory
	{
	public:

		template<typename T>
		static TypeInfo* Get()
		{
			TypeInfo* tpinfo = g_type_factory->__Get(typeid(T).raw_name());
			if (tpinfo == nullptr)
			{
				// 还没这个类型
				// 开始记录这个类型
				auto value = std::make_pair(std::string((&typeid(T))->raw_name()), new TypeInfo(&typeid(T), GlobalData::Instance->GetTypeIndex()));
				value.second->create_instance = nullptr;
				g_type_factory->m_all_type_info.insert(value);

				g_type_factory->m_full_to_raw_name.emplace((value.second->name.c_str() + 6), value.second->raw_name);
				g_type_factory->m_index_to_raw_name.emplace(value.second->index, value.second->raw_name);
				
				tpinfo = value.second;
			}
			return tpinfo;
		}

		static TypeInfo* Get(const TypeIndex idx)
		{
			auto found = g_type_factory->m_index_to_raw_name.find(idx);
			if (found == g_type_factory->m_index_to_raw_name.end())
			{
				return nullptr;
			}
			return g_type_factory->__Get(found->second);
		}

		template<typename T>
		static void RegisterInstance()
		{
			static_assert(std::is_base_of<ISupportTypeCreation, T>::value,
				"The registered instance must inherit 'ISupportTypeCreation'");
			TypeInfo* tpinfo;
			auto found = g_type_factory->m_all_type_info.find((&typeid(T))->raw_name());
			if (found == g_type_factory->m_all_type_info.end())
			{
				tpinfo = TypeFactory::Get<T>();
			}
			else {
				tpinfo = found->second;
			}
			if (!tpinfo->create_instance)
			{
				tpinfo->create_instance = []()->std::shared_ptr<ISupportTypeCreation> {
					return std::make_shared<T>();
				};
			}
		}

		template<typename T>
		static std::shared_ptr<T> CreateInstance(const Type& type)
		{
			if (type.m_info == nullptr)
			{
				throw std::exception("不能用空 Type 创建 Instance");
			}
			if (!type.m_info->create_instance)
			{
				return nullptr;
			}
			std::shared_ptr<ISupportTypeCreation> new_obj = type.m_info->create_instance();

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
		TypeInfo* __Get(const std::string& raw_name) {
			auto found = m_all_type_info.find(raw_name);
			if (found == m_all_type_info.end())
			{
				return nullptr;
			}
			return found->second;
		}

	private:
		std::unordered_map<std::string, TypeInfo*>	m_all_type_info;
		// key: full_name  value: raw_name
		std::unordered_map<std::string, std::string> m_full_to_raw_name;
		// key: TypeIndex  value: raw_name
		std::unordered_map<TypeIndex, std::string> m_index_to_raw_name;

	};


	

}




#define typeof(_T)  Type(Model::TypeFactory::Get<_T>())



template<typename T>
static TypeIndex to_typeindex() {
	static TypeIndex type_idx = typeof(T).m_info->index;
	return type_idx;
}

static Type to_type(const TypeIndex idx) {
	return Type(Model::TypeFactory::Get(idx));
}