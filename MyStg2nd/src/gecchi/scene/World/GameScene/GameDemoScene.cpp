#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


GameDemoScene::GameDemoScene(const char* prm_name) : DefaultScene(prm_name) {
	_pFontPlate01 = NEW FontPlateActor("STR01", "P/moji");
	getLordActor()->accept(KIND_EFFECT, _pFontPlate01);
	_pFontPlate02 = NEW FontPlateActor("STR02", "P/moji");
	getLordActor()->accept(KIND_EFFECT, _pFontPlate02);
}
void GameDemoScene::initialize() {

}

void GameDemoScene::processBehavior() {
	DWORD frame = _dwFrame;
	if (frame == 2) {
		//自機表示
		_pFontPlate01->setString(100,100,"MYSTG2nd");
		_TRACE_("GameDemoScene:STAGE1準備開始！");
		getParentScene(Game)->_pGameMainScene->readyStage01();
		GameGlobal::_pSceneCommon->_pMyShip->playAlone(); //下位にオプション等があるし
		_TRACE_("GameDemoScene:OK稼動しますった！");
	}

	if (frame == 60) {
		_pFontPlate02->setString(100,150,"PUSH HIT UI_EXECUTE KEY!");
	}

	if (_dwFrame > 61) {
		if (VB::isPushedDown(VB_UI_EXECUTE)) {
			_TRACE_("GameDemoScene::processFinally STAGE1スタート！！私はSTOP");
			getParentScene(Game)->_pGameMainScene->enableStage01();
			//自分は停止
			stop();
		}
	}

}

void GameDemoScene::processFinal() {

}


GameDemoScene::~GameDemoScene() {
}
