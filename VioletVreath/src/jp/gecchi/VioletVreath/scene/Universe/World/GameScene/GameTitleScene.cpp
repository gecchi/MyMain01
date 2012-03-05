#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

#define GAMETITLE_TIMEOUT (60*20)
GameTitleScene::GameTitleScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "GameTitleScene";
    useProgress(10);
    _pProg->change(GameTitleScene::PROG_INIT);
    pStringBoard01_ = NEW LabelGecchi16Font("STR01");
    getDirector()->addSubGroup(pStringBoard01_);
    pStringBoard02_ = NEW LabelGecchi16Font("STR02");
    getDirector()->addSubGroup(pStringBoard02_);
    pTitleBoard_ = NEW TitleBoard("TitleBoard");
    getDirector()->addSubGroup(pTitleBoard_);

    pMenu_ = NEW MenuBoardTitle("pMenu_");
    getDirector()->addSubGroup(pMenu_);

    pWorldBound_ = NEW WorldBoundTitle("TITLE_BG_WB");
    getDirector()->addSubGroup(pWorldBound_);
    pHoshiBoshi_ = NEW HoshiBoshiTitle("TITLE_BG_HOSHI");
    getDirector()->addSubGroup(pHoshiBoshi_);

    pSeCon_exec_ = connectSeManager("yume_Sbend");

    _pBgmPerformer->useBgm(1);
    _pBgmPerformer->set(0, "BGM_DEMO");
    frame_of_noinput_ = 0;
    active_item_ = 0;

}

void GameTitleScene::onReset() {
    _TRACE_("GameTitleScene::onReset()");
    pStringBoard01_->update("");
    pStringBoard02_->update("");
    pTitleBoard_->locate(PX2CO(100), PX2CO(90));
    _pProg->set(GameTitleScene::PROG_INIT);
}

void GameTitleScene::onActive() {
    pWorldBound_->inactivateImmed();
    pHoshiBoshi_->inactivateImmed();
    pWorldBound_->activate();
    pHoshiBoshi_->activate();
    pWorldBound_->fadein();
    pHoshiBoshi_->fadein();
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
        case GameTitleScene::PROG_INIT: {
            _pProg->change(GameTitleScene::PROG_TITLE);
            break;
        }

        case GameTitleScene::PROG_TITLE: {
            if (_pProg->isJustChanged()) {
                pStringBoard02_->update(PX2CO(400), PX2CO(400), "PUSH UI_EXECUTE TO BEGIN!");
            }
            if (VB->isPushedDown(VB_UI_EXECUTE)) {
                pSeCon_exec_->use()->play();
                _pProg->change(GameTitleScene::PROG_SELECT);


            } else if (_pProg->getFrameInProgress() == GAMETITLE_TIMEOUT) {
                //ボーっと見てた場合
                _TRACE_("GameTitleScene throwEventToUpperTree(EVENT_GAMETITLESCENE_FINISH)");
                throwEventToUpperTree(EVENT_GAMETITLESCENE_FINISH); //普通に終了イベント
                _pProg->change(GameTitleScene::PROG_FINISH); //タイトルシーン終了へ
            }
            break;
        }

        case GameTitleScene::PROG_SELECT: {
            if (_pProg->isJustChanged()) {
                pMenu_->rise(PX2CO(50), PX2CO(350));
                frame_of_noinput_ = _pProg->getFrameInProgress();
            }


            if (pMenu_->getSubMenu()) {
                int d = pMenu_->getSubMenu()->getDecidedIndex();
                if (d >= 0) {
                    if (pMenu_->getSelectedIndex() == MenuBoardTitle::ITEM_QUIT) {
                        if (d == MenuBoardConfirm::ITEM_OK) {
                            PostQuitMessage(0);
                        } else if (d == MenuBoardConfirm::ITEM_CANCEL) {
                            pMenu_->sinkConfirm();
                        }
                    }
                }
            } else {
                int d = pMenu_->getDecidedIndex();
                if (d >= 0) {
                    if (d == MenuBoardTitle::ITEM_GAME_START) {
                        pSeCon_exec_->use()->play();
                        _pProg->change(GameTitleScene::PROG_GAMESTART);
                    } else if (d == MenuBoardTitle::ITEM_CONFIG) {

                    } else if (d == MenuBoardTitle::ITEM_DEBUG) {

                    } else if (d == MenuBoardTitle::ITEM_QUIT) {
                        pMenu_->riseConfirm();
                    }
                }
            }

            if (VB->getState() != VB_NEUTRAL_STC) { //
                frame_of_noinput_ = _pProg->getFrameInProgress();
            }

            if (_pProg->getFrameInProgress() >= frame_of_noinput_ + GAMETITLE_TIMEOUT) {
                //ボーっと見てた場合
                _TRACE_("GameTitleScene throwEventToUpperTree(EVENT_GAMETITLESCENE_FINISH)");
                throwEventToUpperTree(EVENT_GAMETITLESCENE_FINISH); //普通に終了イベント
                _pProg->change(GameTitleScene::PROG_FINISH); //タイトルシーン終了へ
            }
            break;
        }

        case GameTitleScene::PROG_GAMESTART: {
            if (_pProg->isJustChanged()) {
            }
            if (_pProg->getFrameInProgress() == 90) {
                throwEventToUpperTree(EVENT_GAMESTART);      //スタートでに終了イベント
                _pProg->change(GameTitleScene::PROG_FINISH); //タイトルシーン終了へ
            }
            //点滅
            if (_pProg->getFrameInProgress() % 10 < 5 ) {
                pStringBoard02_->update(PX2CO(700), PX2CO(200), "READY GO!");
            } else {
                pStringBoard02_->update(PX2CO(700), PX2CO(200), "");
            }
            break;
        }

        case GameTitleScene::PROG_FINISH: {
            if (_pProg->isJustChanged()) {
                pMenu_->sink();
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

GameTitleScene::~GameTitleScene() {
//    DELETEARR_IMPOSSIBLE_NULL(papStringItem_);
    pSeCon_exec_->close();
}
