#pragma once
#include "Object.h"


class EventSystem:
	public Object
{
public:
	EventSystem();


	friend class GameSystem;
};