#include "stdafx.h"


Stage01Scene::Stage01Scene(string prm_name) : DefaultScene(prm_name) {
	_bgm_st1 = NULL; //�H��Őݒ肳���
	_TRACE_("Stage01Scene::Finally ���͂����Ȃ莩����~�BGameMainScene���������Ă����܂ő҂�");
}

void Stage01Scene::initialize() {
}

void Stage01Scene::processBehavior() {
}



void Stage01Scene::processJudgement() {
	//�����蔻�菈�����s
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
