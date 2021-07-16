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



		private:
			std::unordered_map<Type, std::list<std::shared_ptr<IBaseAttribute>>>	m_all_attr;

		};





	}
}