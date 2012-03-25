#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;



GameBeginningScene::GameBeginningScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "GameBeginningScene";

    pStringBoard01_ = NEW LabelGecchi16Font("STR01");
    getDirector()->addSubGroup(KIND_EFFECT, pStringBoard01_);
    pStringBoard02_ = NEW LabelGecchi16Font("STR02");
    getDirector()->addSubGroup(KIND_EFFECT, pStringBoard02_);
    selected_stage_ = 0;
    useProgress(GameBeginningScene::PROG_FINISH);
}

void GameBeginningScene::onReset() {
    _TRACE_("GameBeginningScene::onReset()");
    _pProg->change(GameBeginningScene::PROG_INIT);
//    fadeinScene(0);
    pStringBoard01_->update("");
    pStringBoard02_->update("");
    pStringBoard02_->_pFader->stopImmed();
    pStringBoard02_->_pFader->setAlphaToTop();
}
//void GameBeginningScene::ready() {
//    _TRACE_("GameBeginningScene::ready()");
//}
void GameBeginningScene::onActive() {
}

void GameBeginningScene::initialize() {
}

void GameBeginningScene::processBehavior() {

    switch (_pProg->get()) {
        case GameBeginningScene::PROG_INIT: {
            _pProg->change(GameBeginningScene::PROG_SELECT_MODE);
            break;
        }

        case GameBeginningScene::PROG_SELECT_MODE: {
            if (_pProg->isJustChanged()) {
                pStringBoard01_->update(PX2CO(200), PX2CO(200), "GAME_BEGINNING_SCENE BEGIN");
                pStringBoard02_->update(PX2CO(200), PX2CO(250), "SELECT MODE!");
            }
            if (_pProg->get() == GameBeginningScene::PROG_SELECT_MODE) {
                if (VB->isPushedDown(VB_UI_EXECUTE) || _pProg->getFrameInProgress() == 300) {
                    _pProg->change(GameBeginningScene::PROG_DECIDE);
                }
            }
            break;
        }

        case GameBeginningScene::PROG_DECIDE: {
            if (_pProg->isJustChanged()) {
                pStringBoard02_->update(PX2CO(300), PX2CO(300), "OK OK OK");
                pStringBoard02_->_pFader->beat(20,3,7,3,-1);
//                fadeoutScene(FADE_FRAMES);
            }
            if (_pProg->getFrameInProgress() == 20) {
                throwEventToUpperTree(EVENT_GAMEMODE_DECIDE);
            }

//
//            if (_pProg->getFrameInProgress() == FADE_FRAMES) {
//                _pProg->change(GameBeginningScene::PROG_FINISH);
//            }
            break;
        }

        case GameBeginningScene::PROG_FINISH: {
            if (_pProg->isJustChanged()) {
                //inactivate();
            }
            break;
        }

        default:
            break;
    }
    pStringBoard02_->_pFader->behave();
}

GameBeginningScene::~GameBeginningScene() {
}