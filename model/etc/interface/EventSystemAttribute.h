#pragma once
#include "reflection/reflection.h"



namespace Model
{
	class Event : public Reflection::BaseAttribute<Event>
	{
	public:
		Event() = delete;
		Event(const std::string& event_id) {
			EventId = event_id;
		}

		std::string EventId;
	};

	class ObjEvent : public Reflection::BaseAttribute<Event>
	{
	public:
		ObjEvent() = delete;
		ObjEvent(const std::string& event_id) {
			EventId = event_id;
		}

		std::string EventId;
	};

}