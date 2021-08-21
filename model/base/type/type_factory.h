#pragma once
#include "type.h"
#include "interface/ISupportTypeCreation.h"



namespace Model
{

	extern class TypeFactory* g_type_factory;

	class TypeFactory
	{
	public:

		template<typename T>
		static TypeInfo* Get()
		{
			auto found = g_type_factory->m_all_type_info.find((&typeid(T))->raw_name());
			if (found == g_type_factory->m_all_type_info.end())
			{
				auto value = std::make_pair(std::string((&typeid(T))->raw_name()), new TypeInfo(&typeid(T)));
				value.second->create_instance = nullptr;
				value.second->delete_instance = nullptr;
				found = g_type_factory->m_all_type_info.insert(value).first;
			}
			return found->second;
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
				tpinfo->create_instance = []()->void* {
					T* new_obj = new T();
					return new_obj;
				};
				tpinfo->delete_instance = [](void* self)->void {
					delete (T*)self;
				};
			}
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
			std::shared_ptr<ISupportTypeCreation> new_obj((ISupportTypeCreation*)(type.m_info->create_instance()), type.m_info->delete_instance);

			std::shared_ptr<T> ret_obj = std::dynamic_pointer_cast<T>(new_obj);
			if (!ret_obj)
			{
				return nullptr;
			}
			//new_obj->m_self_type = Type(Model::g_type_factory->Get<T>());
			new_obj->BeginInit();
			new_obj->EndInit();
			return ret_obj;
		}
	private:
		std::unordered_map<std::string, TypeInfo*>	m_all_type_info;

	};


	

}




#define typeof(_T)  Type(Model::TypeFactory::Get<_T>())
