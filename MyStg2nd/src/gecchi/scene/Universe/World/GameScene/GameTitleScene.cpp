#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

#define GAMETITLE_TIMEOUT (60*20)
GameTitleScene::GameTitleScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "GameTitleScene";
    useProgress(10);
    _pProg->change(GameTitleScene::PROG_INIT);
    _pStringBoard01 = NEW LabelGecchi16Font("STR01");
    getDirector()->addSubGroup(_pStringBoard01);
    _pStringBoard02 = NEW LabelGecchi16Font("STR02");
    getDirector()->addSubGroup(_pStringBoard02);
    _pTitleBoard = NEW TitleBoard("TitleBoard");
    getDirector()->addSubGroup(_pTitleBoard);

    _pMenu = NEW MenuBoardTitle("_pMenu");
    getDirector()->addSubGroup(_pMenu);

    _pWorldBound = NEW WorldBoundTitle("TITLE_BG_WB");
    getDirector()->addSubGroup(_pWorldBound);
    _pHoshiBoshi = NEW HoshiBoshiTitle("TITLE_BG_HOSHI");
    getDirector()->addSubGroup(_pHoshiBoshi);

    _pSeCon_exec = connectSeManager("yume_Sbend");

    _pBgmPerformer->useBgm(1);
    _pBgmPerformer->set(0, "BGM_DEMO");
    _frame_of_noinput = 0;
    _active_item = 0;

}

void GameTitleScene::onReset() {
    _TRACE_("GameTitleScene::onReset()");
    _pStringBoard01->update("");
    _pStringBoard02->update("");
    _pTitleBoard->locate(PX2CO(100), PX2CO(90));
    _pProg->set(GameTitleScene::PROG_INIT);
}

void GameTitleScene::onActive() {
    _pWorldBound->inactivateImmed();
    _pHoshiBoshi->inactivateImmed();
    _pWorldBound->activate();
    _pHoshiBoshi->activate();
    _pWorldBound->fadein();
    _pHoshiBoshi->fadein();
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
                _pStringBoard02->update(PX2CO(400), PX2CO(400), "PUSH UI_EXECUTE TO BEGIN!");
            }
            if (VB->isPushedDown(VB_UI_EXECUTE)) {
                _pSeCon_exec->use()->play();
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
                _pMenu->rise(PX2CO(50), PX2CO(350));
                _frame_of_noinput = _pProg->getFrameInProgress();
            }


            if (_pMenu->getSubMenu()) {
                int d = _pMenu->getSubMenu()->getDecidedIndex();
                if (d >= 0) {
                    if (_pMenu->getSelectedIndex() == MenuBoardTitle::ITEM_QUIT) {
                        if (d == MenuBoardConfirm::ITEM_OK) {
                            PostQuitMessage(0);
                        } else if (d == MenuBoardConfirm::ITEM_CANCEL) {
                            _pMenu->sinkConfirm();
                        }
                    }
                }
            } else {
                int d = _pMenu->getDecidedIndex();
                if (d >= 0) {
                    if (d == MenuBoardTitle::ITEM_GAME_START) {
                        _pSeCon_exec->use()->play();
                        _pProg->change(GameTitleScene::PROG_GAMESTART);
                    } else if (d == MenuBoardTitle::ITEM_CONFIG) {

                    } else if (d == MenuBoardTitle::ITEM_DEBUG) {

                    } else if (d == MenuBoardTitle::ITEM_QUIT) {
                        _pMenu->riseConfirm();
                    }
                }
            }

            if (VB->getState() != VB_NEUTRAL_STC) { //
                _frame_of_noinput = _pProg->getFrameInProgress();
            }

            if (_pProg->getFrameInProgress() >= _frame_of_noinput + GAMETITLE_TIMEOUT) {
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
                _pStringBoard02->update(PX2CO(700), PX2CO(200), "READY GO!");
            } else {
                _pStringBoard02->update(PX2CO(700), PX2CO(200), "");
            }
            break;
        }

        case GameTitleScene::PROG_FINISH: {
            if (_pProg->isJustChanged()) {
                _pMenu->sink();
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
//    DELETEARR_IMPOSSIBLE_NULL(_papStringItem);
    _pSeCon_exec->close();
}
