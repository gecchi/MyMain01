#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

GameTitleScene::GameTitleScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "GameTitleScene";
    useProgress(10);
    _pPrg->change(GAMEDEMO_SCENE_PROG_INIT);
    _pStringBoard01 = NEW LabelGecchi16Font("STR01");
    getLordActor()->addSubGroup(_pStringBoard01);
    _pStringBoard02 = NEW LabelGecchi16Font("STR02");
    getLordActor()->addSubGroup(_pStringBoard02);
    _pTitleBoard = NEW TitleBoard("TitleBoard");
    getLordActor()->addSubGroup(_pTitleBoard);

    _max_menu_item = 4;
    _paStringItem = NEW LabelGecchi16Font*[_max_menu_item];
    for (int i = 0; i < _max_menu_item; i++) {
        _papStringItem[i] = NEW LabelGecchi16Font("menu_item");
        _papStringItem[i]->inactivateImmediately();
        getLordActor()->addSubGroup(_papStringItem[i]);
    }
    _papStringItem[0]->update("GAME START");
    _papStringItem[1]->update("CONFIG");
    _papStringItem[2]->update("DEBUG");
    _papStringItem[3]->update("HOGEHOGE");

    _pCursor001= NEW Cursor001("Cursor001");
    _pCursor001->inactivateImmediately();
    getLordActor()->addSubGroup(_pCursor001);

    LabelGecchi16Font("STR02");

    _pBgmPerformer->useBgm(1);
    _pBgmPerformer->set(0, "BGM_DEMO");

}
void GameTitleScene::onReset() {
    _TRACE_("GameTitleScene::onReset()");
    _pStringBoard01->update("");
    _pStringBoard02->update("");
    _pTitleBoard->locate(200, 150);
    _pPrg->set(GAMETITLE_SCENE_PROG_INIT);
    unblindScene();
}

void GameTitleScene::onActive() {
}

void GameTitleScene::initialize() {
    _TRACE_("GameTitleScene::initialize()");
}

void GameTitleScene::processBehavior() {

    switch (_pPrg->getFromChange()) {
        default: {
            break;
        }
    }


    switch (_pPrg->get()) {
        case GAMETITLE_SCENE_PROG_INIT: {
            _pPrg->change(GAMETITLE_SCENE_PROG_TITLE);
            break;
        }

        case GAMETITLE_SCENE_PROG_TITLE: {
            if (_pPrg->isJustChanged()) {
                _pStringBoard02->update(400, 500, "PUSH UI_EXECUTE TO BEGIN!");
            }
            if (VB->isPushedDown(VB_UI_EXECUTE)) {
                _TRACE_("GameTitleScene throwEventToUpperTree(EVENT_GAMESTART)");
                _pPrg->change(GAMETITLE_SCENE_PROG_SELECT);
            } else if (_pPrg->getActivePartFrameInProgress() == 240) {
                //ボーっと見てた場合
                _TRACE_("GameTitleScene throwEventToUpperTree(EVENT_GAMETITLE_SCENE_FINISH)");
                throwEventToUpperTree(EVENT_GAMETITLE_SCENE_FINISH); //普通に終了イベント
                _pPrg->change(GAMETITLE_SCENE_PROG_FINISH); //タイトルシーン終了へ
            }
            break;
        }
        case GAMETITLE_SCENE_PROG_SELECT: {
            _pStringBoard02->update("");
            if (_pPrg->isJustChanged()) {
                for (int i = 0; i < _max_menu_item; i++) {
                    _papStringItem[i]->_pStringBoard02->update(200, 500+(i*20));
                    _papStringItem[i]->activate();
                }

            }



            //ボーっと見てた場合
            _TRACE_("GameTitleScene throwEventToUpperTree(EVENT_GAMETITLE_SCENE_FINISH)");
            throwEventToUpperTree(EVENT_GAMETITLE_SCENE_FINISH); //普通に終了イベント
            _pPrg->change(GAMETITLE_SCENE_PROG_FINISH); //タイトルシーン終了へ
            break;
        }


        case GAMETITLE_SCENE_PROG_GAMESTART:
            if (_pPrg->isJustChanged()) {
            }
            if (_pPrg->getActivePartFrameInProgress() == 90) {
                throwEventToUpperTree(EVENT_GAMESTART);      //スタートでに終了イベント
                _pPrg->change(GAMETITLE_SCENE_PROG_FINISH); //タイトルシーン終了へ
            }
            //点滅
            if (_pPrg->getActivePartFrameInProgress() % 10 < 5 ) {
                _pStringBoard02->update(400, 500, "READY GO!");
            } else {
                _pStringBoard02->update(400, 500, "");
            }
            break;

        case GAMETITLE_SCENE_PROG_FINISH:
            if (_pPrg->isJustChanged()) {
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
