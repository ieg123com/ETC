#pragma once
#include <atomic>

namespace Model
{
	
	extern class GlobalData *g_global_data;

	/**
	 * @brief	全局数据
	 */
	class GlobalData
	{
	public:
		GlobalData();


		static int64_t GetObjectID() {
			return (++(g_global_data->m_object_id));
		}

		static int64_t GetAttributeID() {
			return (++(g_global_data->m_attribute_id));
		}

	private:
		std::atomic<int64_t> m_object_id;
		std::atomic<int64_t> m_attribute_id;

	};


}