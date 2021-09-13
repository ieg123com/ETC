#pragma once
#include <atomic>

namespace Model
{
	

	/**
	 * @brief	全局数据
	 */
	class GlobalData
	{
	public:
		GlobalData();

		static GlobalData* Instance;


		static int64_t InstanceId() {
			return (++(GlobalData::Instance->m_object_id));
		}

		static int64_t GetAttributeID() {
			return (++(GlobalData::Instance->m_attribute_id));
		}

		static uint32_t GetTypeIndex() {
			return (++(GlobalData::Instance->m_type_index));
		}
		
		static uint32_t GetEventIndex() {
			return (++(GlobalData::Instance->m_event_index));
		}

		static int64_t ObjectID() {
			return GlobalData::Instance->m_object_id;
		}

		static int64_t AttributeID() {
			return GlobalData::Instance->m_attribute_id;
		}

		static uint32_t TypeIndex() {
			return GlobalData::Instance->m_type_index;
		}

		static uint32_t EventIndex() {
			return GlobalData::Instance->m_event_index;
		}

	private:
		std::atomic<int64_t> m_object_id;
		std::atomic<int64_t> m_attribute_id;
		std::atomic<uint32_t> m_type_index;
		std::atomic<uint32_t> m_event_index;

	};


}