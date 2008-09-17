#include "stdafx.h"


GameDemoScene::GameDemoScene(string prm_name) : DefaultScene(prm_name) {
}

void GameDemoScene::initialize() {

}

void GameDemoScene::processBehavior() {
	DWORD frame = _dwFrame;
	if (frame == 2) {
		//自機表示
		GameGlobal::_pSceneCommon->_pMyShipActor->declarePlay();
		_TRACE_("GameDemoScene:OK稼動しますった！");
	}

	if (frame == 60) {
		_TRACE_("GameDemoScene:STAGE1準備開始！");
		((GameMainScene*)getNext())->readyStage01();
	}
}

void GameDemoScene::processFinal() {
	if (_dwFrame > 300) {
		if (VirtualButton::isPushedDown(VB_UI_EXECUTE)) {

			_TRACE_("GameDemoScene::processFinally STAGE1スタート！！私はSTOP");
			((GameMainScene*)getNext())->enableStage01();

			//自分は停止
			declareStop();
		}
	}
}


GameDemoScene::~GameDemoScene() {
}
