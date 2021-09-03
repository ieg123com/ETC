#pragma once
#include "log/log.h"



#ifdef ETC_EXPORTS
#define ETC_EXPORT __declspec(dllexport)
#else
#define ETC_EXPORT __declspec(dllimport)
#endif




// 后续接入json

typedef long long ObjectID;

// 使用这个，没法查找引用
//typedef EntityEventType EventType;


