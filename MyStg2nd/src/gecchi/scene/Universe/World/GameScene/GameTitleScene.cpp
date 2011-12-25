#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

enum {
    GAMETITLESCENE_PROG_INIT = 1 ,
    GAMETITLESCENE_PROG_TITLE    ,
    GAMETITLESCENE_PROG_SELECT   ,
    GAMETITLESCENE_PROG_GAMESTART,
    GAMETITLESCENE_PROG_FINISH   ,
};
#define GAMETITLE_TIMEOUT 240


GameTitleScene::GameTitleScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "GameTitleScene";
    useProgress(10);
    _pProg->change(GAMETITLESCENE_PROG_INIT);
    _pStringBoard01 = NEW LabelGecchi16Font("STR01");
    getDirector()->addSubGroup(_pStringBoard01);
    _pStringBoard02 = NEW LabelGecchi16Font("STR02");
    getDirector()->addSubGroup(_pStringBoard02);
    _pTitleBoard = NEW TitleBoard("TitleBoard");
    getDirector()->addSubGroup(_pTitleBoard);

    _max_menu_item = 4;
    _papStringItem = NEW LabelGecchi16Font*[_max_menu_item];
    for (int i = 0; i < _max_menu_item; i++) {
        _papStringItem[i] = NEW LabelGecchi16Font("menu_item");
        _papStringItem[i]->_Z = 1;
        _papStringItem[i]->inactivateImmed();
        getDirector()->addSubGroup(_papStringItem[i]);
    }
    _papStringItem[0]->update("GAME START", ALIGN_LEFT, VALIGN_MIDDLE);
    _papStringItem[1]->update("CONFIG", ALIGN_LEFT, VALIGN_MIDDLE);
    _papStringItem[2]->update("DEBUG", ALIGN_LEFT, VALIGN_MIDDLE);
    _papStringItem[3]->update("QUIT", ALIGN_LEFT, VALIGN_MIDDLE);

    _pCursor001= NEW Cursor001("Cursor001");
    _pCursor001->setAlign(ALIGN_LEFT, VALIGN_MIDDLE);
    _pCursor001->inactivateImmed();
    getDirector()->addSubGroup(_pCursor001);

    _pSeCon_exec = connectSeManager("yume_Sbend");

    _pBgmPerformer->useBgm(1);
    _pBgmPerformer->set(0, "BGM_DEMO");

    _active_item = 0;

}
void GameTitleScene::onReset() {
    _TRACE_("GameTitleScene::onReset()");
    _pStringBoard01->update("");
    _pStringBoard02->update("");
    _pTitleBoard->locate(200000, 100000);
    _pProg->set(GAMETITLESCENE_PROG_INIT);
//    fadeinScene(0);
}

void GameTitleScene::onActive() {
}

void GameTitleScene::initialize() {
    _TRACE_("GameTitleScene::initialize()");
}

void GameTitleScene::processBehavior() {

    switch (_pProg->getPrev_WhenJustChanged()) {
        default: {
            break;
        }
    }


    switch (_pProg->get()) {
        case GAMETITLESCENE_PROG_INIT: {
            _pProg->change(GAMETITLESCENE_PROG_TITLE);
            break;
        }

        case GAMETITLESCENE_PROG_TITLE: {
            if (_pProg->isJustChanged()) {
                _pStringBoard02->update(PX2CO(400), PX2CO(400), "PUSH UI_EXECUTE TO BEGIN!");
            }
            if (VB->isPushedDown(VB_UI_EXECUTE)) {
                _pSeCon_exec->use()->play();
                _pProg->change(GAMETITLESCENE_PROG_SELECT);


            } else if (_pProg->getFrameInProgress() == GAMETITLE_TIMEOUT) {
                //ボーっと見てた場合
                _TRACE_("GameTitleScene throwEventToUpperTree(EVENT_GAMETITLESCENE_FINISH)");
                throwEventToUpperTree(EVENT_GAMETITLESCENE_FINISH); //普通に終了イベント
                _pProg->change(GAMETITLESCENE_PROG_FINISH); //タイトルシーン終了へ
            }
            break;
        }

        case GAMETITLESCENE_PROG_SELECT: {
            if (_pProg->isJustChanged()) {
                _pStringBoard02->update("");
                if (_pProg->isJustChanged()) {
                    for (int i = 0; i < _max_menu_item; i++) {
                        _papStringItem[i]->locate(PX2CO(700)+PX2CO(i*20), PX2CO(100+(i*20))*2);
                        _papStringItem[i]->activate();
                    }
                }
                _active_item = 0;
                _pCursor001->locateAs(_papStringItem[_active_item]);
                _pCursor001->activate();
                _frame_of_noinput = _pProg->getFrameInProgress();
            }
            _pCursor001->moveTo(_papStringItem[_active_item]);

            if (VB->isAutoRepeat(VB_UI_UP)) {
                _active_item--;
                if (_active_item < 0) {
                    _active_item = _max_menu_item-1;
                }
                _frame_of_noinput = _pProg->getFrameInProgress();
            } else if (VB->isAutoRepeat(VB_UI_DOWN)) {
                _active_item++;
                if (_active_item > _max_menu_item-1) {
                    _active_item = 0;
                }
                _frame_of_noinput = _pProg->getFrameInProgress();
            } if (VB->isPushedDown(VB_UI_EXECUTE)) {

                if (_active_item == 0) {
                    _pSeCon_exec->use()->play();
                    _pProg->change(GAMETITLESCENE_PROG_GAMESTART);
                } else if (_active_item == 1) {


                } else if (_active_item == 2) {


                } else if (_active_item == 3) {
                    PostQuitMessage(0);
                }



            } else if (_pProg->getFrameInProgress() >= _frame_of_noinput + 300) {
                //ボーっと見てた場合
                _TRACE_("GameTitleScene throwEventToUpperTree(EVENT_GAMETITLESCENE_FINISH)");
                throwEventToUpperTree(EVENT_GAMETITLESCENE_FINISH); //普通に終了イベント
                _pProg->change(GAMETITLESCENE_PROG_FINISH); //タイトルシーン終了へ
            }
            break;
        }

        case GAMETITLESCENE_PROG_GAMESTART: {
            if (_pProg->isJustChanged()) {
            }
            if (_pProg->getFrameInProgress() == 90) {
                throwEventToUpperTree(EVENT_GAMESTART);      //スタートでに終了イベント
                _pProg->change(GAMETITLESCENE_PROG_FINISH); //タイトルシーン終了へ
            }
            //点滅
            if (_pProg->getFrameInProgress() % 10 < 5 ) {
                _pStringBoard02->update(PX2CO(700), PX2CO(200), "READY GO!");
            } else {
                _pStringBoard02->update(PX2CO(700), PX2CO(200), "");
            }
            break;
        }

        case GAMETITLESCENE_PROG_FINISH: {
            if (_pProg->isJustChanged()) {
//                fadeoutSceneTree(FADE_FRAMES);
//                inactivateDelay(FADE_FRAMES);
            }
            //おしまい待ちぼうけループ
            break;
        }

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
