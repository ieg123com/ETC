#include "attribute.h"
#include "GlobalData.h"

namespace Model
{

	Attribute::Attribute()
	{
		m_id = GlobalData::GetAttributeID();
	}

}