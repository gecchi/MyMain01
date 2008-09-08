#include "stdafx.h"


GameDemoScene::GameDemoScene(string prm_name) : DefaultScene(prm_name) {
}

void GameDemoScene::initialize() {

}

void GameDemoScene::processBehavior() {
	DWORD frame = _dwFrame;
	// 以下の gen start ～ end はマクロにより自動生成されたコードです。変更はマクロから行って下さい。
	// gen start
	// gen end

	if (frame == 2) {
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

			//_pMyShipSceneの移動
			((GameMainScene*)getNext())->_pStage01Scene->addSubLast(((GameScene*)getParent())->_pMyShipScene->becomeIndependent()); //シーンをplayしてから追加しないと玉が飛び散る
			declareStop();
		}
	}

}


GameDemoScene::~GameDemoScene() {
}
