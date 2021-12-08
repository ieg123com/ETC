#include "GlobalData.h"


namespace Model
{
	GlobalData* GlobalData::Instance = nullptr;

	GlobalData::GlobalData()
	{
		m_object_id = 0;
		m_attribute_id = 0;
		m_type_index = 0;
		m_event_index = 0;
		m_async_task_id = 0;
	}
}