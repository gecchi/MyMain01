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




	_pStage01Scene = NULL;
	_pStage02Scene = NULL;
	_pStage03Scene = NULL;
	_pStage04Scene = NULL;
	_pStage05Scene = NULL;


	_dwFrame_ReadyStage01 = 0;
	_dwFrame_ReadyStage02 = 0;
	_dwFrame_ReadyStage03 = 0;
	_dwFrame_ReadyStage04 = 0;
	_dwFrame_ReadyStage05 = 0;

	_readyStage01Flg = false;
	_readyStage02Flg = false;
	_readyStage03Flg = false;
	_readyStage04Flg = false;
	_readyStage05Flg = false;

}

void GameMainScene::initialize() {

}

void GameMainScene::readyStage01() {
	_TRACE_("GameMainScene::readyStage01() : よし工場にcreateStage01Scene注文しました");
	orderSceneToFactory(ORDER_ID_CREATESTAGE01SCENE, Stage01Scene, "Stage01");
	_readyStage01Flg = true;
	_dwFrame_ReadyStage01 = _dwFrame;
}

void GameMainScene::enableStage01() {
	_TRACE_("GameMainScene::enableStage01 おっしゃSTAGE1起動じゃ");
	if (_pStage01Scene == NULL) {
//		_TRACE_("GameMainScene::enableStage01() : _pStage01Sceneがまだ出来てません！、ちょっと待ちます。");
//		for(int i = 0; _pStage01Scene == NULL; i++) {
//			Sleep(10);
//			if (i == 1000) {
//				throw_GgafCriticalException("GameMainScene::enableStage01() : 待ちきれませんでした！");
//			}
//		}
		return;
	}

	_pStage01Scene->play();
}



void GameMainScene::readyStage02() {
	getSub("Demo")->farewell();
	orderSceneToFactory(ORDER_ID_CREATESTAGE02SCENE, Stage02Scene, "Stage02");
	_readyStage02Flg = true;
	_dwFrame_ReadyStage02 = _dwFrame;
}

void GameMainScene::enableStage02() {
	if (_pStage02Scene == NULL) {
//		_TRACE_("GameMainScene::enableStage02() 1: _pStage02Sceneがまだ出来てません！、ちょっと待ちます。")
//		for(int i = 0; _pStage02Scene != NULL; i++) {
//			Sleep(10);
//			if (i == 1000) {
//				throw_GgafCriticalException("GameMainScene::enableStage02() : 待ちきれませんでした！");
//			}
//		}
		return;
 	}
	_pStage02Scene->play();
}


void GameMainScene::readyStage03() {
}

void GameMainScene::enableStage03() {
}

void GameMainScene::readyStage04() {
}

void GameMainScene::enableStage04() {
}

void GameMainScene::readyStage05() {
}

void GameMainScene::enableStage05() {
}


void GameMainScene::processBehavior() {
	DWORD frame = _dwFrame;

	if (_readyStage01Flg) {
		if (frame == (_dwFrame_ReadyStage01 + 180)) {  //180フレーム余裕をみてから自シーンに追加
			_pStage01Scene = obtainSceneFromFactory(ORDER_ID_CREATESTAGE01SCENE);
			addSubLast(_pStage01Scene);
			_readyStage01Flg = false;
			_TRACE_("GameMainScene::processBehavior : やったよ、Stage01追加したよ");
		}
	}

	if (_readyStage02Flg) {
		if (frame == _dwFrame_ReadyStage02+180) {
			_pStage02Scene  = obtainSceneFromFactory(ORDER_ID_CREATESTAGE02SCENE);
			addSubLast(_pStage02Scene);
			_readyStage02Flg = false;
		}
	}

	if (_readyStage03Flg) {
		if (frame == _dwFrame_ReadyStage03+180) {
			_pStage03Scene  = MyFactory::obtainScene(ORDER_ID_CREATESTAGE03SCENE);
			addSubLast(_pStage03Scene);
			_readyStage03Flg = false;
		}
	}

	if (_readyStage04Flg) {
		if (frame == _dwFrame_ReadyStage04+300) {
			_pStage04Scene  = MyFactory::obtainScene(ORDER_ID_CREATESTAGE04SCENE);
			addSubLast(_pStage04Scene);
			_readyStage04Flg = false;
		}
	}

	if (_readyStage05Flg) {
		if (frame == _dwFrame_ReadyStage05+300) {
			_pStage05Scene  = MyFactory::obtainScene(ORDER_ID_CREATESTAGE05SCENE);
			addSubLast(_pStage05Scene);
			_readyStage05Flg = false;
		}
	}

	//SCORE表示
	sprintf(_buf, "SCORE:%07u", GameGlobal::_dwScore);
	_pFontPlate_SCORE->setString(500,0,_buf);
}

void GameMainScene::processFinal() {
}

GameMainScene::~GameMainScene() {
}
