#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

GameScene::GameScene(const char* prm_name) : DefaultScene(prm_name) {
	_pGameDemo = NEW GameDemoScene("GameDemo");
	_pGameDemo->refrainImmediatelyAlone(); //非活動
	addSubLast(_pGameDemo);

	_pGameMain = NEW GameMainScene("GameMain");
	_pGameDemo->refrainImmediatelyAlone(); //非活動
	addSubLast(_pGameMain);

	_pSceneCannel = _pGameDemo;


	_pCommonScene = NEW CommonScene("Common");
	addSubLast(_pCommonScene);

}


void GameScene::cannelGameDemo() {
	_pGameDemo->refrain();
	_pSceneCannel = _pGameDemo;
	_pGameMain->act();
}

void GameScene::cannelGameMain() {
	_pGameDemo->refrain();
	_pSceneCannel = _pGameMain;
	_pGameMain->act();
}

void GameScene::initialize() {
	_TRACE_("GameScene::initialize() いきますよDemoSceneさん");
	cannelGameDemo();
}


void GameScene::processBehavior() {
	VB::update(); //入力情報更新
#ifdef OREDEBUG
	//ワイヤフレーム表示切替
	if (VB::isPushedDown(VB_UI_DEBUG)) {
		if (GgafDx9God::_d3dfillmode == D3DFILL_WIREFRAME) {
			GgafDx9God::_d3dfillmode = D3DFILL_SOLID;
		} else {
			GgafDx9God::_d3dfillmode = D3DFILL_WIREFRAME;
		}
	}
#endif
	if (_pSceneCannel == _pGameDemo) {
		if (_pGameDemo->chkProgressOnChange() == GAMEDEMO_PROG_GAMESTART_BEGIN) {
			orderSceneToFactory(1, GameMainScene, "GameMain");
			setProgress(GAME_PROG_DEMO_BEGIN);
		} else if (_dwFrame == getFrameAtProgress(GAME_PROG_DEMO_BEGIN)+120) {
			_pGameMain = (GameMainScene*)obtainSceneFromFactory(1);
			_pGameMain->setStage(1);
			setProgress(GAME_PROG_DEMO_DISP);
			cannelGameMain();
		}
	} else if (_pSceneCannel == _pGameMain) {

	}
}

void GameScene::processFinal() {
}

GameScene::~GameScene() {
}
