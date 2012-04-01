#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

GamePreTitleScene::GamePreTitleScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "GamePreTitleScene";
    useProgress(10);
    _pProg->change(GamePreTitleScene::PROG_INIT);
    pLabel01_ = NEW LabelGecchi16Font("STR01");
    getDirector()->addSubGroup(pLabel01_);
    pLabel02_ = NEW LabelGecchi16Font("STR02");
    getDirector()->addSubGroup(pLabel02_);
    pTitleBoard_ = NEW TitleBoard("TitleBoard");
    getDirector()->addSubGroup(pTitleBoard_);
}
void GamePreTitleScene::onReset() {
    _TRACE_("GamePreTitleScene::onReset()");
    pTitleBoard_->locate(PXCO(100), PXCO(600));
    pLabel01_->update("");
    pLabel02_->update("");
//    fadeoutScene(0);
    _pProg->change(GamePreTitleScene::PROG_INIT);
}

void GamePreTitleScene::onActive() {
}

void GamePreTitleScene::initialize() {
    _TRACE_("GamePreTitleScene::initialize()");
}

void GamePreTitleScene::processBehavior() {

    switch (_pProg->get()) {
        case GamePreTitleScene::PROG_INIT: {
            _pProg->change(GamePreTitleScene::PROG_EXEC);
            break;
        }

        case GamePreTitleScene::PROG_EXEC: {
            if (_pProg->isJustChanged()) {
//                fadeinScene(FADE_FRAMES);
            }
            if (_pProg->getFrameInProgress() == 1) {
                pLabel01_->update(PXCO(100), PXCO(50), "[STORY]");
            } else if (_pProg->getFrameInProgress() == 120) {
                pLabel01_->update(PXCO(100), PXCO(50), "MUKASHI MUKASHI ARU TOKORONI.");
            } else if (_pProg->getFrameInProgress() == 240) {
                pLabel01_->update(PXCO(100), PXCO(50), "MA SORE HA OITOITE...");
            } else if (_pProg->getFrameInProgress() == 360) {
                pLabel01_->update(PXCO(100), PXCO(50), "TORIAEZU TEKI WO TAOSINI IKOUZE ! BY GECCHI");
            } else if (_pProg->getFrameInProgress() > 361) {
                //タイトルが下からニューっと
                pTitleBoard_->_Y -= PXCO(1);
                if (pTitleBoard_->_Y <= PXCO(90)) {
                    pTitleBoard_->_Y = PXCO(90);
                    _pProg->change(GamePreTitleScene::PROG_FINISH);
                }
            }
            break;
        }

        case GamePreTitleScene::PROG_FINISH: {
            if (_pProg->isJustChanged()) {
                throwEventToUpperTree(EVENT_PREGAMETITLESCENE_FINISH);
//                inactivate();
            }
            //おしまい待ちぼうけループ
            break;
        }

        default:
            break;
     }
}

GamePreTitleScene::~GamePreTitleScene() {
}
