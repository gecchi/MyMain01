#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


GameDemoScene::GameDemoScene(const char* prm_name) : DefaultScene(prm_name) {
	setProgress(GAMEDEMO_PROG_INIT);
	_pFontPlate01 = NEW FontPlateActor("STR01", "P/moji");
	getLordActor()->accept(KIND_EFFECT, _pFontPlate01);
	_pFontPlate02 = NEW FontPlateActor("STR02", "P/moji");
	getLordActor()->accept(KIND_EFFECT, _pFontPlate02);
}
void GameDemoScene::initialize() {

}

void GameDemoScene::processBehavior() {
	if (_dwFrame == getFrameAtProgress(GAMEDEMO_PROG_INIT)+2) {
		//自機表示
		GameGlobal::_pSceneCommon->_pMyShip->actAlone(); //下位にオプション等があるし
		setProgress(GAMEDEMO_PROG_BEGIN);
		_TRACE_("GameDemoScene:OK稼動しますった！");
	}

	if (_dwFrame == getFrameAtProgress(GAMEDEMO_PROG_BEGIN)+50) {
		setProgress(GAMEDEMO_PROG_TITLE_BEGIN);
	}
//ループ----->

	if (getProgress() == GAMEDEMO_PROG_TITLE_BEGIN) {
		//タイトル表示
		_pFontPlate01->setString(100,100,"TITLE：MYSTG2nd");
		_pFontPlate02->setString(100,150,"PUSH HIT UI_EXECUTE KEY!");
		setProgress(GAMEDEMO_PROG_TITLE_DISP);
	} else if (_dwFrame == getFrameAtProgress(GAMEDEMO_PROG_TITLE_DISP)+100) {
		setProgress(GAMEDEMO_PROG_DEMOPLAY_BEGIN);
	} else if (getProgress() == GAMEDEMO_PROG_DEMOPLAY_BEGIN) {
		//デモプレイ表示
		_pFontPlate01->setString(100,100,"DEMOPLAY!：MYSTG2nd");
		setProgress(GAMEDEMO_PROG_DEMOPLAY_DISP);
	} else if (_dwFrame == getFrameAtProgress(GAMEDEMO_PROG_DEMOPLAY_DISP)+300) {
		setProgress(GAMEDEMO_PROG_RANKING_BEGIN);
	} else if (getProgress() == GAMEDEMO_PROG_RANKING_BEGIN) {
		//ランキング表示
		_pFontPlate01->setString(100,100,"RANKING!!!：MYSTG2nd");
		setProgress(GAMEDEMO_PROG_RANKING_BEGIN_DISP);
	} else if (_dwFrame == getFrameAtProgress(GAMEDEMO_PROG_RANKING_BEGIN_DISP)+300) {
		setProgress(GAMEDEMO_PROG_TITLE_BEGIN);
	}
//<-----ループ
	//デモプレイかランキング時
	if (GAMEDEMO_PROG_DEMOPLAY_BEGIN <= getProgress() || getProgress() <= GAMEDEMO_PROG_RANKING_DISP) {
		if (VB::isPushedDown(VB_UI_EXECUTE)) {
			_TRACE_("GameDemoScene タイトルへ");
			setProgress(GAMEDEMO_PROG_TITLE_BEGIN);
		}
	}

	//タイトル画面時
	if (getProgress() == GAMEDEMO_PROG_TITLE_DISP) {
		if (VB::isPushedDown(VB_UI_EXECUTE)) {
			_TRACE_("GameDemoScene スタート押しました！！");
			setProgress(GAMEDEMO_PROG_GAMESTART_BEGIN);
		}
	}

	//ゲームスタート
	if (getProgress() == GAMEDEMO_PROG_GAMESTART_BEGIN) {
		_pFontPlate01->setString(100,100,"GAME START!");
		setProgress(GAMEDEMO_PROG_GAMESTART_AFTER);
	}

	//ゲームスタート後
	if (getProgress() == GAMEDEMO_PROG_GAMESTART_AFTER) {
		//
	}


}

void GameDemoScene::processFinal() {

}


GameDemoScene::~GameDemoScene() {
}
