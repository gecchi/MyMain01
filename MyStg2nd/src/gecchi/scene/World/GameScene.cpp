#include "stdafx.h"


GameScene::GameScene(string prm_name) : DefaultScene(prm_name) {
	_pGameDemoScene = NEW GameDemoScene("GameDemo");
	_pGameDemoScene -> stopImmediately();
	addSubLast(_pGameDemoScene);

	_pGameMainScene = NEW GameMainScene("GameMain");
	addSubLast(_pGameMainScene);

	_pCommonScene = NEW CommonScene("Common");
	addSubLast(_pCommonScene);
}

void GameScene::initialize() {

}


void GameScene::processBehavior() {
	VB::update(); //入力情報更新
}


void GameScene::processFinal() {
	if (_dwFrame == 120) {
		GgafDx9SeManager::get("logon")->play();
		_TRACE_("GameScene いきますよDemoSceneさん");
		_pGameDemoScene->declarePlay();
	}
}


GameScene::~GameScene() {
}
