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
    _papStringItem = NEW LabelGecchi16Font*[_max_menu_item];
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

    _pSeCon_exec = (GgafDx9SeConnection*)GgafDx9Sound::_pSeManager->getConnection("yume_Sbend");

    _pBgmPerformer->useBgm(1);
    _pBgmPerformer->set(0, "BGM_DEMO");

    _active_item = 0;

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
                _pSeCon_exec->refer()->play();
                _pPrg->change(GAMETITLE_SCENE_PROG_SELECT);
            } else if (_pPrg->getFrameInProgress() == GAMETITLE_TIMEOUT) {
                //ボーっと見てた場合
                _TRACE_("GameTitleScene throwEventToUpperTree(EVENT_GAMETITLE_SCENE_FINISH)");
                throwEventToUpperTree(EVENT_GAMETITLE_SCENE_FINISH); //普通に終了イベント
                _pPrg->change(GAMETITLE_SCENE_PROG_FINISH); //タイトルシーン終了へ
            }
            break;
        }
        case GAMETITLE_SCENE_PROG_SELECT: {
            if (_pPrg->isJustChanged()) {
                _pStringBoard02->update("");
                if (_pPrg->isJustChanged()) {
                    for (int i = 0; i < _max_menu_item; i++) {
                        _papStringItem[i]->update(200, 500+(i*20));
                        _papStringItem[i]->activate();
                    }
                }
                _active_item = 0;
                _pCursor001->locateAs(_papStringItem[_active_item]);
                _pCursor001->activate();
                _frame_of_noinput = _pPrg->getFrameInProgress();
            }
            _pCursor001->locateAs(_papStringItem[_active_item]);


            if (VB->isAutoRepeat(VB_UI_UP)) {
                _active_item--;
                if (_active_item < 0) {
                    _active_item = _max_menu_item-1;
                }
                _frame_of_noinput = _pPrg->getFrameInProgress();
            } else if (VB->isAutoRepeat(VB_UI_DOWN)) {
                _active_item++;
                if (_active_item > _max_menu_item-1) {
                    _active_item = 0;
                }
                _frame_of_noinput = _pPrg->getFrameInProgress();
            } else if (_pPrg->getFrameInProgress() >= _frame_of_noinput + 300) {
                //ボーっと見てた場合
                _TRACE_("GameTitleScene throwEventToUpperTree(EVENT_GAMETITLE_SCENE_FINISH)");
                throwEventToUpperTree(EVENT_GAMETITLE_SCENE_FINISH); //普通に終了イベント
                _pPrg->change(GAMETITLE_SCENE_PROG_FINISH); //タイトルシーン終了へ
            }
            break;
        }

        case GAMETITLE_SCENE_PROG_GAMESTART:
            if (_pPrg->isJustChanged()) {
            }
            if (_pPrg->getFrameInProgress() == 90) {
                throwEventToUpperTree(EVENT_GAMESTART);      //スタートでに終了イベント
                _pPrg->change(GAMETITLE_SCENE_PROG_FINISH); //タイトルシーン終了へ
            }
            //点滅
            if (_pPrg->getFrameInProgress() % 10 < 5 ) {
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
    DELETEARR_IMPOSSIBLE_NULL(_papStringItem);
    _pSeCon_exec->close();
}
