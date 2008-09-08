#include "stdafx.h"


GameScene::GameScene(string prm_name) : DefaultScene(prm_name) {
	_pGameDemoScene = NEW GameDemoScene("GameDemo");
	_pGameDemoScene -> stopImmediately();
	addSubLast(_pGameDemoScene);

	_pGameMainScene = NEW GameMainScene("GameMain");
	addSubLast(_pGameMainScene);

	_pMyShipScene = NEW MyShipScene("MyShip");
	_pMyShipScene -> stopImmediately();
}

void GameScene::initialize() {

}


void GameScene::processBehavior() {
	VirtualButton::update(); //入力情報更新

	//DWORD frame = _dwFrame;
	// 以下の gen start ～ end はマクロにより自動生成されたコードです。変更はマクロから行って下さい。
	// gen start
	// gen end


}


void GameScene::processFinal() {
	if (_dwFrame == 120) {
		GgafDx9SeManager::get("logon")->play();
		_TRACE_("GameScene いきますよDemoSceneさん");
		_pGameDemoScene->addSubLast(_pMyShipScene);
		_pGameDemoScene->declarePlay();
	}
}


GameScene::~GameScene() {
}
