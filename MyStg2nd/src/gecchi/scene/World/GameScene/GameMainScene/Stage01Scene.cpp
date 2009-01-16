#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


Stage01Scene::Stage01Scene(string prm_name) : DefaultScene(prm_name) {
	Stage01MainScene* pStage01MainScene = NEW Stage01MainScene("Stage01Main");
	BackGround01Plate* pBack = NEW BackGround01Plate("BACKGOROUND01", "");
	getLordActor()->accept(KIND_EFFECT, pBack);
	addSubLast(pStage01MainScene);
	_bgm_st1 = GgafDx9BgmManager::get("JM5");
	_bgm_st1->play(false);
	stopImmediately(); //GameMainScene���������Ă����
	_TRACE_("Stage01Scene::Finally ���͂����Ȃ莩����~�BGameMainScene���������Ă����܂ő҂�");
}

void Stage01Scene::initialize() {
}

void Stage01Scene::processBehavior() {
}



void Stage01Scene::processJudgement() {
	//�����蔻�菈�����s
	//�ڍׂ� ACTOR.xls �� hantei �V�[�g
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
