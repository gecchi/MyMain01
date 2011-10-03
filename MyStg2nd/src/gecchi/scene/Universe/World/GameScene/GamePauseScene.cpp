#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

enum {
    GAMEPAUSESCENE_PROG_INIT = 1 ,
    GAMEPAUSESCENE_PROG_SELECT   ,
    GAMEPAUSESCENE_PROG_CONFIRM  ,
    GAMEPAUSESCENE_PROG_FINISH   ,
};

GamePauseScene::GamePauseScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "GamePauseScene";
    useProgress(10);
    _pProg->change(GAMEPAUSESCENE_PROG_INIT);
    _pMsgLabel01 = NEW LabelGecchi16Font("STR01");
    _pMsgLabel01->update("PAUSE!!");
    getDirector()->addSubGroup(_pMsgLabel01);
    _pMsgLabel02 = NEW LabelGecchi16Font("STR02");
    _pMsgLabel02->update("YOU SURE ?");
    getDirector()->addSubGroup(_pMsgLabel02);

    const char* item[] = {
          "BACK TO GAME",
          "CONFIG",
          "BACK TO TITLE",
          "QUIT GAME"
    };
    _max_menu_item = 4;
    _papMenuItemLabel = NEW LabelGecchi16Font*[_max_menu_item];
    for (int i = 0; i < _max_menu_item; i++) {
        _papMenuItemLabel[i] = NEW LabelGecchi16Font("menu_item");
        _papMenuItemLabel[i]->_Z = 1;
        _papMenuItemLabel[i]->update(item[i], ALIGN_CENTER, VALIGN_MIDDLE);
        _papMenuItemLabel[i]->inactivateImmediately();
        getDirector()->addSubGroup(_papMenuItemLabel[i]);
    }

    _pCursor001= NEW Cursor001("Cursor001");
    _pCursor001->inactivateImmediately();
    getDirector()->addSubGroup(_pCursor001);

    _pSeCon_exec = connectSeManager("click07_2");
    _active_item = 0;

}
void GamePauseScene::onReset() {
    _TRACE_("GamePauseScene::onReset()");
    _pMsgLabel01->inactivateImmediately();
    _pMsgLabel02->inactivateImmediately();
    for (int i = 0; i < _max_menu_item; i++) {
        _papMenuItemLabel[i]->inactivateImmediately();
    }
    _pProg->set(GAMEPAUSESCENE_PROG_INIT);
}

void GamePauseScene::onActive() {
}

void GamePauseScene::initialize() {
    _TRACE_("GamePauseScene::initialize()");
}

void GamePauseScene::processBehavior() {

    switch (_pProg->getPrev_WhenJustChanged()) {
        default: {
            break;
        }
    }


    switch (_pProg->get()) {
        case GAMEPAUSESCENE_PROG_INIT: {
            _pProg->change(GAMEPAUSESCENE_PROG_SELECT);
            break;
        }

        case GAMEPAUSESCENE_PROG_SELECT: {
            if (_pProg->isJustChanged()) {
                //アイテム
                for (int i = 0; i < _max_menu_item; i++) {
                    //初期設定
                    _papMenuItemLabel[i]->locate(Pix2App(-256), Pix2App(0));
                    _papMenuItemLabel[i]->activateDelay(i*10+1); //パラパラと順に
                    //飛ばす
                    coord tX = Pix2App(1000);
                    coord tY = Pix2App(200+i*32);
                    _papMenuItemLabel[i]->_pKurokoA->setMvAng(tX, tY);
                    _papMenuItemLabel[i]->_pKurokoA->execSmoothMvVeloSequence(
                                                        0,
                                                        GgafDxUtil::getDistance(_papMenuItemLabel[i]->_X, _papMenuItemLabel[i]->_Y, tX, tY),
                                                        30,
                                                        0.3, 0.7);
                }

                //カーソル
                _pCursor001->locateAs(_papMenuItemLabel[_active_item]);
                _pCursor001->activate();
            }
            //メインループ

            _pCursor001->moveTo(_papMenuItemLabel[_active_item]);
            if (VB->isAutoRepeat(VB_UI_UP)) {
                _pSeCon_exec->use()->play();
                _active_item--;
                if (_active_item < 0) {
                    _active_item = _max_menu_item-1;
                }
                _frame_of_noinput = _pProg->getFrameInProgress();
            } else if (VB->isAutoRepeat(VB_UI_DOWN)) {
                _pSeCon_exec->use()->play();
                _active_item++;
                if (_active_item > _max_menu_item-1) {
                    _active_item = 0;
                }
                _frame_of_noinput = _pProg->getFrameInProgress();
            } if (VB->isPushedDown(VB_UI_EXECUTE)) {

                if (_active_item == 0) {

//                    _pProg->change(GAMEPAUSESCENE_PROG_GAMESTART);
                } else if (_active_item == 1) {


                } else if (_active_item == 2) {
                    _pProg->change(GAMEPAUSESCENE_PROG_CONFIRM);

                } else if (_active_item == 3) {
//                    _pProg->change(GAMEPAUSESCENE_PROG_CONFIRM);
                    PostQuitMessage(0);
                }
            }
            break;
        }

        case GAMEPAUSESCENE_PROG_CONFIRM: {

            break;
        }

        case GAMEPAUSESCENE_PROG_FINISH: {
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



    for (int i = 0; i < _max_menu_item; i++) {
        if (_papMenuItemLabel[i]->isActiveActor()) {
            _papMenuItemLabel[i]->_pKurokoA->behave();
        }
    }
    _pMsgLabel01->_pKurokoA->behave();
    _pMsgLabel02->_pKurokoA->behave();

}

void GamePauseScene::processFinal() {

}

GamePauseScene::~GamePauseScene() {
    DELETEARR_IMPOSSIBLE_NULL(_papMenuItemLabel);
    _pSeCon_exec->close();
}
