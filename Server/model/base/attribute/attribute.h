#pragma once
#include <stdint.h>
#include <memory>
#include "interface/ISupportTypeCreation.h"

namespace Model
{
	using AttrID = int64_t;


	class Attribute:
		public ISupportTypeCreation,
		public std::enable_shared_from_this<Attribute>
	{
	public:
		Attribute();

		virtual AttrID GetAttrID() { return m_id; }
	private:
		AttrID m_id;
	};


}