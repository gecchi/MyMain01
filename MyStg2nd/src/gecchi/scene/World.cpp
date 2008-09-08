#include "stdafx.h"


World::World(string prm_name) : DefaultWorld(prm_name) {
	GameScene* pGameScene = NEW GameScene("Game");
	addSubLast(pGameScene);
#ifdef OREDEBUG
	DispFpsActor* pDispFpsActor = NEW DispFpsActor("FPS_STRING", "moji");
	getLordActor()->accept(KIND_EFFECT, pDispFpsActor);
#endif
}

World::~World() {
}
