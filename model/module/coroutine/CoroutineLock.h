#pragma once
#include "kernel/Entity.h"
#include "coroutine.h"


using namespace Model;

class CoroutineLock:
	public GEntity
{
public:
	using co_lock = co::ConditionVariableAnyT<void*>;
	
	//co::LFLock Lock;


// 	void Lock();
// 
// 
// 	void UnLock();






};