#include "stdafx.h"


Stage01MainScene::Stage01MainScene(string prm_name) : DefaultScene(prm_name) {

	// 以下の gen start ～ end はマクロにより自動生成されたコードです。変更はマクロから行って下さい。
	// gen01 start
	DWORD dw[] = {1,5};
	_paFrame_NextEvent = new DWORD[2];
	for (int i = 0; i < 2; i++) {
		_paFrame_NextEvent[i] = dw[i];
	}
	// gen01 end
	stopImmediately(); //GameMainSceneが解除してくれる
}

void Stage01MainScene::initialize() {
}

void Stage01MainScene::processBehavior() {
	// 以下の gen start ～ end はマクロにより自動生成されたコードです。変更はマクロから行って下さい。
	// gen02 start
	if (_dwFrame == _paFrame_NextEvent[_iCnt_Event]) {
		switch (_dwFrame) {
			case 1:
				MyFactory::orderActor("[104-6]5", MyFactory::createEnemyCeres, NULL);
				break;
			case 5:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[104-6]5"));
				break;
			default :
				break;
		}
		_iCnt_Event++;
	}
	// gen02 end

	if (_dwFrame == 2) {

		_TRACE_("Stage01MainScene::processBehavior はいはいDemoさんありがとう、私も起動しましたよ");
		// 共通シーンを配下に移動
		addSubLast(GameGlobal::_pSceneCommon->tear());

	}


}

void Stage01MainScene::processFinal() {
//	if (_dwFrame == 1) {
//		_TRACE_("Stage01MainScene::processFinally 私はいきなり停止します。GameMainSceneが解除してくれるはずー");
//		this->declareStop(); //GameMainSceneが解除してくれる
//	}
}

Stage01MainScene::~Stage01MainScene() {
}
