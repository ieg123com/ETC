#include "dll.h"
#include <stdio.h>
#include "single/ISingletonHandle.h"
#include "type/type.h"
#include "Game.h"
#include "base/start.h"
#include "base/init.h"



void Awake()
{
	
}

void Init(const Model::stGlobalVar& global)
{
	Model::SetGlobalVar(global);

	// �������
	Hotfix::Start();
}


void Destroy()
{

}