#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

#define GAMETITLE_TIMEOUT (60*20)
GameTitleScene::GameTitleScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "GameTitleScene";
    useProgress(10);
    _pProg->set(GameTitleScene::PROG_INIT);

    pLabel01_ = NEW LabelGecchi16Font("STR01");
    getDirector()->addSubGroup(pLabel01_);

    pLabel02_ = NEW LabelGecchi16Font("STR02");
    getDirector()->addSubGroup(pLabel02_);

    pTitleBoard_ = NEW TitleBoard("TitleBoard");
    getDirector()->addSubGroup(pTitleBoard_);

    pMenu_ = NEW MenuBoardTitle("pMenu_");
    getDirector()->addSubGroup(pMenu_);

    pWorldBound_ = NEW WorldBoundTitle("TITLE_BG_WB");
    getDirector()->addSubGroup(pWorldBound_);

    pHoshiBoshi_ = NEW HoshiBoshiTitle("TITLE_BG_HOSHI");
    getDirector()->addSubGroup(pHoshiBoshi_);

    pSeCon_exec_ = connectToSeManager("WAVE_EXECUTE");

    //_pBgmPerformer->useBgm(1);
   // _pBgmPerformer->set(0, "OGG_BGM_DEMO");
    frame_of_noinput_ = 0;
    active_item_ = 0;

}

void GameTitleScene::onReset() {
    _TRACE_("GameTitleScene::onReset()");
    pLabel01_->update("");
    pLabel02_->update("");
    pTitleBoard_->locate(PX_C(100), PX_C(90));
    _pProg->set(GameTitleScene::PROG_INIT);
}

void GameTitleScene::onActive() {
    pWorldBound_->inactivateImmed();
    pHoshiBoshi_->inactivateImmed();
    pWorldBound_->activate();
    pHoshiBoshi_->activate();
    pWorldBound_->fadein();
    pHoshiBoshi_->fadein();
    _pProg->set(GameTitleScene::PROG_INIT);
}

void GameTitleScene::initialize() {
    _TRACE_("GameTitleScene::initialize()");
}

void GameTitleScene::processBehavior() {

    switch (_pProg->getFromProgOnChange()) {
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
            if (_pProg->hasJustChanged()) {
                pLabel02_->update(PX_C(400), PX_C(400), "PUSH UI_EXECUTE TO BEGIN!");
            }
            if (VB->isPushedDown(VB_UI_EXECUTE)) {
                pSeCon_exec_->fetch()->play();
                _pProg->change(GameTitleScene::PROG_SELECT);
            } else if (_pProg->getFrameInProgress() == GAMETITLE_TIMEOUT) {
                //ボーっと見てた場合
                _TRACE_("GameTitleScene throwEventUpperTree(EVENT_GAMETITLESCENE_FINISH)");
                throwEventUpperTree(EVENT_GAMETITLESCENE_FINISH); //普通に終了イベント
                _pProg->change(GameTitleScene::PROG_FINISH); //タイトルシーン終了へ
            }
            break;
        }

        case GameTitleScene::PROG_SELECT: {
            if (_pProg->hasJustChanged()) {
                pMenu_->rise(PX_C(50), PX_C(250));
                frame_of_noinput_ = _pProg->getFrameInProgress();
            }

            if (pMenu_->canControll()) {
                if (pMenu_->getDecidedIndex() == MenuBoardTitle::ITEM_GAME_START) {
                    pMenu_->disableControll(); //入力受付終わり
                    pSeCon_exec_->fetch()->play();
                    _pProg->change(GameTitleScene::PROG_GAMESTART);
                }
            }

            if (VB->getState() != VB_NEUTRAL_STC || pMenu_->getRisingSubMenu()->isActive()) { //
                frame_of_noinput_ = _pProg->getFrameInProgress();
            }

            if (_pProg->getFrameInProgress() >= frame_of_noinput_ + GAMETITLE_TIMEOUT) {
                //ボーっと見てた場合
                _TRACE_("GameTitleScene throwEventUpperTree(EVENT_GAMETITLESCENE_FINISH)");
                throwEventUpperTree(EVENT_GAMETITLESCENE_FINISH); //普通に終了イベント
                _pProg->change(GameTitleScene::PROG_FINISH); //タイトルシーン終了へ
            }
            break;
        }

        case GameTitleScene::PROG_GAMESTART: {
            if (_pProg->hasJustChanged()) {
            }
            if (_pProg->getFrameInProgress() == 90) {
                throwEventUpperTree(EVENT_GAMESTART);      //スタートでに終了イベント
                _pProg->change(GameTitleScene::PROG_FINISH); //タイトルシーン終了へ
            }
            //点滅
            if (_pProg->getFrameInProgress() % 10 < 5 ) {
                pLabel02_->update(PX_C(700), PX_C(200), "READY GO!");
            } else {
                pLabel02_->update(PX_C(700), PX_C(200), "");
            }
            break;
        }

        case GameTitleScene::PROG_FINISH: {
            if (_pProg->hasJustChanged()) {
                pMenu_->sink();
//                fadeoutSceneWithBgmTree(FADE_FRAMES);
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
