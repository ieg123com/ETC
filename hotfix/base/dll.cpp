#include "dll.h"
#include <stdio.h>
#include "single/ISingletonHandle.h"
#include "type/type.h"
#include "Game.h"
#include "base/start.h"



void Awake()
{
	
}

void Init(const Model::stGlobalVar& global)
{
	Model::g_type_factory = global.type_factory;
	Model::g_singleton_factory = global.single_factory;
	Model::g_game = global.game;


	// º”‘ÿÕÍ≥…
	Hotfix::Start();
}


void Destroy()
{

}