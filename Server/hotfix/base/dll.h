#pragma once
#include "helper/hotfix/HotfixHelper.h"



#define API extern "C" __declspec(dllexport)



API void Awake();


API void Init(const Model::stGlobalVar& global);


API void Destroy();

