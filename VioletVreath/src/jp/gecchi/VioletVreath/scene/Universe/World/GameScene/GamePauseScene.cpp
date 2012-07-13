#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

GamePauseScene::GamePauseScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "GamePauseScene";

    pMenuBoardPause_ = NEW MenuBoardPause("MenuBoardPause");
    getDirector()->addSubGroup(pMenuBoardPause_);

    useProgress(10);
    _pProg->change(GamePauseScene::PROG_INIT);
    pMsgLabel01_ = NEW LabelGecchi16Font("STR01");
    pMsgLabel01_->update("PAUSE!!");
    getDirector()->addSubGroup(pMsgLabel01_);
    pMsgLabel02_ = NEW LabelGecchi16Font("STR02");
    pMsgLabel02_->update("YOU SURE ?");
    getDirector()->addSubGroup(pMsgLabel02_);

    const char* item[] = {
          "BACK TO GAME",
          "CONFIG",
          "BACK TO TITLE",
          "QUIT GAME"
    };
    max_menu_item_ = 4;
    papMenuItemLabel_ = NEW LabelGecchi16Font*[max_menu_item_];
    for (int i = 0; i < max_menu_item_; i++) {
        papMenuItemLabel_[i] = NEW LabelGecchi16Font("menu_item");
        papMenuItemLabel_[i]->_Z = 1;
        papMenuItemLabel_[i]->update(item[i], ALIGN_CENTER, VALIGN_MIDDLE);
        papMenuItemLabel_[i]->inactivateImmed();
        getDirector()->addSubGroup(papMenuItemLabel_[i]);
    }

    pCursor001_= NEW Cursor001("Cursor001");
    pCursor001_->setAlign(ALIGN_CENTER, VALIGN_MIDDLE);
    pCursor001_->inactivateImmed();
    getDirector()->addSubGroup(pCursor001_);

    pSeCon_exec_ = connectToSeManager("click07");
    active_item_ = 0;

}

void GamePauseScene::onReset() {
    _TRACE_("GamePauseScene::onReset()");
    pMsgLabel01_->inactivateImmed();
    pMsgLabel02_->inactivateImmed();
    for (int i = 0; i < max_menu_item_; i++) {
        papMenuItemLabel_[i]->_pKurokoA->setMvVelo(0);
        papMenuItemLabel_[i]->inactivateImmed();
    }
    pCursor001_->_pKurokoA->setMvVelo(0);
    pCursor001_->inactivateImmed();
    _pProg->set(GamePauseScene::PROG_INIT);
}

void GamePauseScene::onActive() {
    pMenuBoardPause_->rise();
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
        case GamePauseScene::PROG_INIT: {
            _pProg->change(GamePauseScene::PROG_SELECT);
            break;
        }

        case GamePauseScene::PROG_SELECT: {
            if (_pProg->isJustChanged()) {


                //アイテム
                for (int i = 0; i < max_menu_item_; i++) {
                    //初期設定
                    papMenuItemLabel_[i]->locate(PX_C(-256), PX_C(0));
                    papMenuItemLabel_[i]->activateDelay(i*10+1); //パラパラと順に
                    //飛ばす
                    coord tX = PX_C(1000);
                    coord tY = PX_C(200+i*32);
                    papMenuItemLabel_[i]->_pKurokoA->setMvAng(tX, tY);
                    papMenuItemLabel_[i]->_pKurokoA->execSmoothMvSequence(
                                                        0,
                                                        UTIL::getDistance(papMenuItemLabel_[i]->_X, papMenuItemLabel_[i]->_Y, tX, tY),
                                                        30,
                                                        0.3, 0.7);
                }

                //カーソル
                pCursor001_->locateWith(papMenuItemLabel_[active_item_]);
                pCursor001_->activate();
            }
            //メインループ

            pCursor001_->moveTo(papMenuItemLabel_[active_item_]);
            if (VB->isAutoRepeat(VB_UI_UP)) {
                pSeCon_exec_->fetch()->play();
                active_item_--;
                if (active_item_ < 0) {
                    active_item_ = max_menu_item_-1;
                }
                frame_of_noinput_ = _pProg->getFrameInProgress();
            } else if (VB->isAutoRepeat(VB_UI_DOWN)) {
                pSeCon_exec_->fetch()->play();
                active_item_++;
                if (active_item_ > max_menu_item_-1) {
                    active_item_ = 0;
                }
                frame_of_noinput_ = _pProg->getFrameInProgress();
            } if (VB->isPushedDown(VB_UI_EXECUTE)) {

                if (active_item_ == 0) {

//                    _pProg->change(GamePauseScene::PROG_GAMESTART);
                } else if (active_item_ == 1) {


                } else if (active_item_ == 2) {
                    _pProg->change(GamePauseScene::PROG_CONFIRM);

                } else if (active_item_ == 3) {
//                    _pProg->change(GamePauseScene::PROG_CONFIRM);
                    PostQuitMessage(0);
                }
            }
            break;
        }

        case GamePauseScene::PROG_CONFIRM: {

            break;
        }

        case GamePauseScene::PROG_FINISH: {
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



    for (int i = 0; i < max_menu_item_; i++) {
        if (papMenuItemLabel_[i]->isActiveInTheTree()) {
            papMenuItemLabel_[i]->_pKurokoA->behave();
        }
    }
    pMsgLabel01_->_pKurokoA->behave();
    pMsgLabel02_->_pKurokoA->behave();
}

void GamePauseScene::onInactive() {
    pMenuBoardPause_->sink();
}

GamePauseScene::~GamePauseScene() {
    DELETEARR_IMPOSSIBLE_NULL(papMenuItemLabel_);
    pSeCon_exec_->close();
}
