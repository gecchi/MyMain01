#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

GameTitleScene::GameTitleScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "GameTitleScene";

    changeProgress(GAMEDEMO_SCENE_PROG_INIT);
    _pStringBoard01 = NEW LabelGecchi16Font("STR01");
    getLordActor()->addSubGroup(_pStringBoard01);
    _pStringBoard02 = NEW LabelGecchi16Font("STR02");
    getLordActor()->addSubGroup(_pStringBoard02);
    _pTitleBoard = NEW TitleBoard("TitleBoard");
    _pTitleBoard->inactivateImmediately();
    getLordActor()->addSubGroup(_pTitleBoard);

    _pBgmPerformer->useBgm(1);
    _pBgmPerformer->set(0, "BGM_DEMO");
}
void GameTitleScene::reset() {
    _pTitleBoard->inactivate();
    changeProgress(GAMEDEMO_SCENE_PROG_INIT);
}

void GameTitleScene::onActive() {
    reset();
}

void GameTitleScene::initialize() {
}

void GameTitleScene::processBehavior() {

    //GAMETITLE_SCENE_PROG_INIT 時の処理
    if (onActiveProgress(GAMETITLE_SCENE_PROG_INIT)) {
    }
    if (getProgress() == GAMETITLE_SCENE_PROG_INIT) {
        changeProgress(GAMETITLE_SCENE_PROG_INIT);
    }
    if (onInactiveProgress(GAMETITLE_SCENE_PROG_INIT)) {
    }


    //タイトル前デモ GAMETITLE_SCENE_PROG_PRE_TITLE 時の処理
    if (onActiveProgress(GAMETITLE_SCENE_PROG_PRE_TITLE)) {
    }
    if (getProgress() == GAMETITLE_SCENE_PROG_PRE_TITLE) {
        if (getActivePartFrame() == 1) {
            _pStringBoard01->update(100, 50, "[STORY]");
        } else if (getActivePartFrame() == 120) {
            _pStringBoard01->update(100, 50, "MUKASHI MUKASHI ARU TOKORONI.");
        } else if (getActivePartFrame() == 240) {
            _pStringBoard01->update(100, 50, "MA SORE HA OITOITE...");
        } else if (getActivePartFrame() == 360) {
            _pStringBoard01->update(100, 50, "TORIAEZU TEKI WO TAOSINI IKOUZE !");
        } else if (getActivePartFrame() == 480) {
            _pStringBoard01->update(100, 50, "GANBARE!!! BY GECCHI");
        } else if (getActivePartFrame() == 600) {
            _pTitleBoard->activate();
        }

        //タイトル表示アニメーション終了でタイトルへ
        if (_pTitleBoard->onActiveProgress(TITLEBOARD_PROG_DISP)) {
            changeProgress(GAMEDEMO_SCENE_PROG_TITLE);
        }

        //VB_UI_EXECUTEで即タイトルへ
        if (VB->isPushedDown(VB_UI_EXECUTE)) {
            changeProgress(GAMEDEMO_SCENE_PROG_TITLE);
        }
    }
    if (onInactiveProgress(GAMETITLE_SCENE_PROG_PRE_TITLE)) {
        _pStringBoard01->update(100, 50, "");
    }

    //タイトル GAMETITLE_SCENE_PROG_TITLE 時の処理
    if (onActiveProgress(GAMETITLE_SCENE_PROG_TITLE)) {
        _pTitleBoard->changeProgress(TITLEBOARD_PROG_DISP);
        _pTitleBoard->activate();
        _pStringBoard02->update(400, 500, "PUSH UI_EXECUTE TO START!");
    }
    if (getProgress() == GAMETITLE_SCENE_PROG_TITLE) {
        //ゲームスタート！
        if (VB->isPushedDown(VB_UI_EXECUTE)) {
            throwEventToUpperTree(EVENT_GAMETITLE_SCENE_GAMESTART);
        }

        //ボーっと見てた場合
        if (getActivePartFrame() == 240) {
            throwEventToUpperTree(EVENT_GAMETITLE_SCENE_FINISH);
        }
    }
    if (onInactiveProgress(GAMETITLE_SCENE_PROG_TITLE)) {
        _pTitleBoard->inactivate();
    }

}

void GameTitleScene::processFinal() {

}

GameTitleScene::~GameTitleScene() {
}
