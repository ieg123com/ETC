#include "GlobalData.h"


namespace Model
{
	GlobalData* GlobalData::Instance = nullptr;

	GlobalData::GlobalData()
	{
		m_object_id = 0;
		m_attribute_id = 0;
	}
}