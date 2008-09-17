#include "stdafx.h"


Stage01Scene::Stage01Scene(string prm_name) : DefaultScene(prm_name) {
	_bgm_st1 = NULL; //Hê‚ÅÝ’è‚³‚ê‚é
	_TRACE_("Stage01Scene::Finally Ž„‚Í‚¢‚«‚È‚èŽ©•ª’âŽ~BGameMainScene‚ª‰ðœ‚µ‚Ä‚­‚ê‚é‚Ü‚Å‘Ò‚Â‚·");
}

void Stage01Scene::initialize() {
}

void Stage01Scene::processBehavior() {
}



void Stage01Scene::processJudgement() {
	//“–‚½‚è”»’èˆ—ŽÀs
	if (_dwFrame >= 2) {
		executeBumpChkHeadActors(KIND_CHIKEI, KIND_MY|KIND_MY_SHOT_GU|KIND_MY_SHOT_CHOKI|KIND_MY_SHOT_NOMAL|KIND_ENEMY_SHOT_GU|KIND_ENEMY_SHOT_CHOKI|KIND_ENEMY_SHOT_NOMAL|KIND_OTHER);
		executeBumpChkHeadActors(KIND_ENEMY|KIND_ENEMY_SHOT_GU|KIND_ENEMY_SHOT_CHOKI|KIND_ENEMY_SHOT_PA|KIND_ENEMY_SHOT_NOMAL|KIND_OTHER, KIND_MY|KIND_MY_SHOT_GU|KIND_MY_SHOT_CHOKI|KIND_MY_SHOT_PA|KIND_MY_SHOT_NOMAL);
		executeBumpChkHeadActors(KIND_OTHER, KIND_ENEMY|KIND_ENEMY_SHOT_GU|KIND_ENEMY_SHOT_CHOKI|KIND_ENEMY_SHOT_PA|KIND_ENEMY_SHOT_NOMAL|KIND_OTHER);
		executeBumpChkHeadActors(KIND_MY_SHOT_CHOKI|KIND_MY_SHOT_NOMAL, KIND_ENEMY_SHOT_GU);
		executeBumpChkHeadActors(KIND_MY_SHOT_CHOKI, KIND_MY_SHOT_GU);
	}
}



void Stage01Scene::processFinal() {

}

Stage01Scene::~Stage01Scene() {
}
