#pragma once
#include "reflection_assembly.h"


namespace Model
{
	namespace Reflection
	{


		template<typename T>
		class ISystem
		{
		public:
			template<typename AT>
			void Add(AT* base_attr)const {
				base_attr->m_obj_type = typeof(T);
				std::shared_ptr<AT> new_attr(base_attr);
				Assembly::Instance().AddAttribute(new_attr);
			}

		};
	}
}