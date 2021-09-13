#pragma once


#include "interface/IAwakeSystem.h"
#include "interface/ILoadSystem.h"
#include "interface/IStartSystem.h"
#include "interface/IUpdateSystem.h"
#include "interface/ILateUpdateSystem.h"
#include "interface/IDestroySystem.h"


#include "interface/ObjectSystemAttribute.h"
#include "interface/EventSystemAttribute.h"

#include "kernel/Object.h"
#include "kernel/Entity.h"
#include "kernel/Component.h"
#include "kernel/ObjectFactory.h"
#include "kernel/ObjectRegisterAction.h"


#include "common/timer/TimerComponent.h"



#include "Game.h"


using namespace Model;