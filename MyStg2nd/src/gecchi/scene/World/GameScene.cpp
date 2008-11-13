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

#ifdef OREDEBUG
	//ワイヤフレーム表示切替
	if (VB::isPushedDown(VB_UI_DEBUG)) {
		_TRACE_("前GgafDx9God::_d3dfillmode="<<GgafDx9God::_d3dfillmode);
		if (GgafDx9God::_d3dfillmode == D3DFILL_WIREFRAME) {
			GgafDx9God::_d3dfillmode = D3DFILL_SOLID;
		} else {
			GgafDx9God::_d3dfillmode = D3DFILL_WIREFRAME;
		}
		_TRACE_("後GgafDx9God::_d3dfillmode="<<GgafDx9God::_d3dfillmode);
	}
#endif
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
