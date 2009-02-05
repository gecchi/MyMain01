#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


#define ORDER_ID_CREATESTAGE01SCENE 11
#define ORDER_ID_CREATESTAGE02SCENE 12
#define ORDER_ID_CREATESTAGE03SCENE 13
#define ORDER_ID_CREATESTAGE04SCENE 14
#define ORDER_ID_CREATESTAGE05SCENE 15

GameMainScene::GameMainScene(const char* prm_name) : DefaultScene(prm_name) {
	_pFontPlate_SCORE = NEW FontPlateActor("STR01", "P/moji");
	getLordActor()->accept(KIND_EFFECT, _pFontPlate_SCORE);
	_stage = 1;
	_pSceneCannel = NULL;
}

void GameMainScene::cannelStage(int prm_cannel) {

	switch (prm_cannel) {
	case 1:
		_pStage01->act();
		_pStage02->refrain();
		_pStage03->refrain();
		_pStage04->refrain();
		_pStage05->refrain();
		_pSceneCannel = _pStage01;
		break;
	case 2:
		_pStage01->refrain();
		_pStage02->act();
		_pStage03->refrain();
		_pStage04->refrain();
		_pStage05->refrain();
		_pSceneCannel = _pStage02;
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	default:
		break;
	}
}

void GameMainScene::initialize() {
	switch (_stage) {
	case 1:
		orderSceneToFactory(11, Stage01Scene, "Stage01");
		break;
	case 2:
		orderSceneToFactory(11, Stage02Scene, "Stage02");
		break;
	case 3:
		orderSceneToFactory(11, Stage03Scene, "Stage03");
		break;
	case 4:
		orderSceneToFactory(11, Stage04Scene, "Stage04");
		break;
	case 5:
		orderSceneToFactory(11, Stage05Scene, "Stage05");
		break;
	default:
		break;
	}
}


void GameMainScene::processBehavior() {
	if (_pSceneCannel->chkProgressOnChange() == STAGE_PROG_PLAY_BEGIN) {
		addSubLast(obtainSceneFromFactory(11));
		setProgress(GAMEMAIN_PROG_STAGE_PLAY_BEGIN);
	} else if (getProgress() == GAMEMAIN_PROG_STAGE_PLAY_BEGIN) {
		setProgress(GAMEMAIN_PROG_STAGE_PLAYING);
	}

	//SCORE•\Ž¦
	sprintf(_buf, "SCORE:%07u", GameGlobal::_dwScore);
	_pFontPlate_SCORE->setString(500,0,_buf);
}

void GameMainScene::processFinal() {
}

GameMainScene::~GameMainScene() {
}



