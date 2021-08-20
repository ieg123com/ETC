#pragma once
#include "reflection/reflection.h"



namespace Model
{
	class Event : public Reflection::BaseAttribute<Event>
	{
	public:
		Event() {}
		Event(const int32_t event_id) {
			EventId = event_id;
		}

		int32_t EventId;
	};

	class ObjEvent : public Reflection::BaseAttribute<ObjEvent>
	{
	public:
		ObjEvent() {}
		ObjEvent(const int32_t event_id) {
			EventId = event_id;
		}

		int32_t EventId;
	};

}