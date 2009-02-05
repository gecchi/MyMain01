#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

bool StageScene::_pause = false;


StageScene::StageScene(const char* prm_name) : DefaultScene(prm_name) {
}

void StageScene::initialize() {
}

void StageScene::processBehavior() {
	//ˆêŽž’âŽ~
	if (VB::isPushedDown(VB_UI_CANCEL)) {
		if (_pause) {
			_pStage01Scene->pause();
		} else {
			_pStage01Scene->unpause();
		}
	}

}

void StageScene::processJudgement() {
}


void StageScene::processFinal() {

}

StageScene::~StageScene() {
}
