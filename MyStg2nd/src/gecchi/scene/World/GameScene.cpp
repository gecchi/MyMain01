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
	VirtualButton::update(); //���͏��X�V
}


void GameScene::processFinal() {
	if (_dwFrame == 120) {
		GgafDx9SeManager::get("logon")->play();
		_TRACE_("GameScene �����܂���DemoScene����");
		_pGameDemoScene->addSubLast(_pMyShipScene);
		_pGameDemoScene->declarePlay();
	}
}


GameScene::~GameScene() {
}
