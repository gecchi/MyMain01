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
    pStringBoard01_ = NEW LabelGecchi16Font("STR01");
    getDirector()->addSubGroup(pStringBoard01_);
    pStringBoard02_ = NEW LabelGecchi16Font("STR02");
    getDirector()->addSubGroup(pStringBoard02_);
    pTitleBoard_ = NEW TitleBoard("TitleBoard");
    getDirector()->addSubGroup(pTitleBoard_);
}
void GamePreTitleScene::onReset() {
    _TRACE_("GamePreTitleScene::onReset()");
    pTitleBoard_->locate(PX2CO(100), PX2CO(600));
    pStringBoard01_->update("");
    pStringBoard02_->update("");
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
                pStringBoard01_->update(PX2CO(100), PX2CO(50), "[STORY]");
            } else if (_pProg->getFrameInProgress() == 120) {
                pStringBoard01_->update(PX2CO(100), PX2CO(50), "MUKASHI MUKASHI ARU TOKORONI.");
            } else if (_pProg->getFrameInProgress() == 240) {
                pStringBoard01_->update(PX2CO(100), PX2CO(50), "MA SORE HA OITOITE...");
            } else if (_pProg->getFrameInProgress() == 360) {
                pStringBoard01_->update(PX2CO(100), PX2CO(50), "TORIAEZU TEKI WO TAOSINI IKOUZE ! BY GECCHI");
            } else if (_pProg->getFrameInProgress() > 361) {
                //�^�C�g����������j���[����
                pTitleBoard_->_Y -= PX2CO(1);
                if (pTitleBoard_->_Y <= PX2CO(90)) {
                    pTitleBoard_->_Y = PX2CO(90);
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
            //�����܂��҂��ڂ������[�v
            break;
        }

        default:
            break;
     }
}

GamePreTitleScene::~GamePreTitleScene() {
}