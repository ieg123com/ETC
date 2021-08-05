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
	Model::DomainTask::Instance().RunAll();
	Game::Event().Add(DLLType::Hotfix, Assembly::GetSharedPtr());

	// º”‘ÿÕÍ≥…
	::Hotfix::Start();
}


void Destroy()
{
	::Hotfix::Over();
}
