#pragma once
#include "reflection/reflection.h"



namespace Model
{
	class Event : public Reflection::BaseAttribute<Event>
	{
	public:
		Event() {}
		Event(const std::string& event_id) {
			EventId = event_id;
		}

		std::string EventId;
	};

	class ObjEvent : public Reflection::BaseAttribute<ObjEvent>
	{
	public:
		ObjEvent() {}
		ObjEvent(const std::string& event_id) {
			EventId = event_id;
		}

		std::string EventId;
	};

}