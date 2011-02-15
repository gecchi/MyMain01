#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

GameTitleScene::GameTitleScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "GameTitleScene";
    useProgress(10);
    _pProgress->change(GAMEDEMO_SCENE_PROG_INIT);
    _pStringBoard01 = NEW LabelGecchi16Font("STR01");
    getLordActor()->addSubGroup(_pStringBoard01);
    _pStringBoard02 = NEW LabelGecchi16Font("STR02");
    getLordActor()->addSubGroup(_pStringBoard02);
    _pTitleBoard = NEW TitleBoard("TitleBoard");
    getLordActor()->addSubGroup(_pTitleBoard);

    _pBgmPerformer->useBgm(1);
    _pBgmPerformer->set(0, "BGM_DEMO");

}
void GameTitleScene::onReset() {
    _TRACE_("GameTitleScene::onReset()");
    _pStringBoard01->update("");
    _pStringBoard02->update("");
    _pTitleBoard->setCoordinate(200, 150);
    _pProgress->change(GAMETITLE_SCENE_PROG_INIT);
    unblindScene();
}

void GameTitleScene::onActive() {
}

void GameTitleScene::initialize() {
    _TRACE_("GameTitleScene::initialize()");
}

void GameTitleScene::processBehavior() {

    switch (_pProgress->getChangedFrom()) {
        default:
            break;
    }


    switch (_pProgress->get()) {
        case GAMETITLE_SCENE_PROG_INIT:
            _pProgress->change(GAMETITLE_SCENE_PROG_TITLE);
            break;

        case GAMETITLE_SCENE_PROG_TITLE:
            if (_pProgress->isJustChanged()) {
                _pStringBoard02->update(400, 500, "PUSH UI_EXECUTE TO START!");
            }
            if (VB->isPushedDown(VB_UI_EXECUTE)) {
                _TRACE_("GameTitleScene throwEventToUpperTree(EVENT_GAMESTART)");
                _pProgress->change(GAMETITLE_SCENE_PROG_GAMESTART);
            } else if (_pProgress->getActivePartFrameInProgress() == 240) {
                //ボーっと見てた場合
                _TRACE_("GameTitleScene throwEventToUpperTree(EVENT_GAMETITLE_SCENE_FINISH)");
                throwEventToUpperTree(EVENT_GAMETITLE_SCENE_FINISH); //普通に終了イベント
                _pProgress->change(GAMETITLE_SCENE_PROG_FINISH); //タイトルシーン終了へ
            }
            break;

        case GAMETITLE_SCENE_PROG_GAMESTART:
            if (_pProgress->isJustChanged()) {
            }
            if (_pProgress->getActivePartFrameInProgress() == 90) {
                throwEventToUpperTree(EVENT_GAMESTART);      //スタートでに終了イベント
                _pProgress->change(GAMETITLE_SCENE_PROG_FINISH); //タイトルシーン終了へ
            }
            //点滅
            if (_pProgress->getActivePartFrameInProgress() % 10 < 5 ) {
                _pStringBoard02->update(400, 500, "READY GO!");
            } else {
                _pStringBoard02->update(400, 500, "");
            }
            break;

        case GAMETITLE_SCENE_PROG_FINISH:
            if (_pProgress->isJustChanged()) {
                fadeoutSceneTree(FADE_FRAME);
                inactivateDelay(FADE_FRAME);
            }
            //おしまい待ちぼうけループ
            break;

        default:
            break;
    }
}

void GameTitleScene::processFinal() {

}

GameTitleScene::~GameTitleScene() {
}
