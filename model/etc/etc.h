#pragma once


#include "interface/IAwakeSystem.h"
#include "interface/ILoadSystem.h"
#include "interface/IStartSystem.h"
#include "interface/IUpdateSystem.h"
#include "interface/ILateUpdateSystem.h"
#include "interface/IDestroySystem.h"
#include "module/message/IActorMessage.h"
#include "module/message/IActorRpcMessage.h"
#include "module/message/IActorLocationMessage.h"
#include "module/message/IActorLocationRpcMessage.h"
#include "module/message/IMessage.h"
#include "module/message/IRpcMessage.h"

#include "interface/ObjectSystemAttribute.h"
#include "interface/EventSystemAttribute.h"
#include "module/message/MessageSystemAttribute.h"

#include "kernel/Object.h"
#include "kernel/Entity.h"
#include "kernel/Component.h"
#include "kernel/ObjectFactory.h"
#include "kernel/ObjectRegisterAction.h"


#include "Game.h"


using namespace Model;