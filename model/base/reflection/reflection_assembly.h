#pragma once
#include <memory>
#include <unordered_map>
#include <list>
#include "type/type.h"
#include "single/ISingleton.h"
#include "reflection_attribute.h"


namespace Model
{
	namespace Reflection
	{

		class IBaseAttribute;

		/**
		 * @brief	反射属性合集
		 */
		class Assembly:
			public IDomainSingleton<Assembly>
		{
		public:


			void AddAttribute(std::shared_ptr<IBaseAttribute> base_attr) {
				m_all_attr[base_attr->GetAttrType()].push_back(base_attr);
			}

			const std::list<std::shared_ptr<IBaseAttribute>>& GetTypeTry(const Type& type)const {
				auto found = m_all_attr.find(type);
				if (found == m_all_attr.end())
				{
					throw std::exception("Assembly 没有找到你需要的类型");
				}
				return found->second;
			}

			template<typename T>
			const std::list<std::shared_ptr<IBaseAttribute>>& GetTypeTry()const {
				return GetTypeTry(typeof(T));
			}


			const std::list<std::shared_ptr<IBaseAttribute>>& GetType(const Type& type)const {
				auto found = m_all_attr.find(type);
				if (found == m_all_attr.end())
				{
					return std::list<std::shared_ptr<IBaseAttribute>>();
				}
				return found->second;
			}

			template<typename T>
			const std::list<std::shared_ptr<IBaseAttribute>>& GetType()const {
				return GetType(typeof(T));
			}

			std::list<std::shared_ptr<IBaseAttribute>> GetAllType()const {
				std::list<std::shared_ptr<IBaseAttribute>> all_attr;
				for (auto& item : m_all_attr)
				{
					for (auto& attr : item.second)
					{
						all_attr.push_back(attr);
					}
				}
				return std::move(all_attr);
			}

		private:
			std::unordered_map<Type, std::list<std::shared_ptr<IBaseAttribute>>>	m_all_attr;

		};





	}
}