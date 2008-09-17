#include "stdafx.h"


GameScene::GameScene(string prm_name) : DefaultScene(prm_name) {
	_pGameDemoScene = NEW GameDemoScene("GameDemo");
	_pGameDemoScene -> stopImmediately();
	addSubLast(_pGameDemoScene);

	_pGameMainScene = NEW GameMainScene("GameMain");
	addSubLast(_pGameMainScene);

	_pCommonScene = NEW CommonScene("MyShip");
	addSubLast(_pCommonScene);
}

void GameScene::initialize() {

}


void GameScene::processBehavior() {
	VirtualButton::update(); //“ü—Íî•ñXV
}


void GameScene::processFinal() {
	if (_dwFrame == 120) {
		GgafDx9SeManager::get("logon")->play();
		_TRACE_("GameScene ‚¢‚«‚Ü‚·‚æDemoScene‚³‚ñ");
		_pGameDemoScene->declarePlay();
	}
}


GameScene::~GameScene() {
}
