#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;



GameBeginningScene::GameBeginningScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "GameBeginningScene";

    _pStringBoard01 = NEW LabelGecchi16Font("STR01");
    getDirector()->addSubGroup(KIND_EFFECT, _pStringBoard01);
    _pStringBoard02 = NEW LabelGecchi16Font("STR02");
    getDirector()->addSubGroup(KIND_EFFECT, _pStringBoard02);
    _selected_stage = 0;
    useProgress(GameBeginningScene::PROG_FINISH);
}

void GameBeginningScene::onReset() {
    _TRACE_("GameBeginningScene::onReset()");
    _pProg->change(GameBeginningScene::PROG_INIT);
//    fadeinScene(0);
    _pStringBoard01->update("");
    _pStringBoard02->update("");
    _pStringBoard02->_pFader->stopImmed();
    _pStringBoard02->_pFader->setAlphaToTop();
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
                _pStringBoard01->update(PX2CO(200), PX2CO(200), "GAME_BEGINNING_SCENE BEGIN");
                _pStringBoard02->update(PX2CO(200), PX2CO(250), "SELECT MODE!");
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
                _pStringBoard02->update(PX2CO(300), PX2CO(300), "OK OK OK");
                _pStringBoard02->_pFader->beat(20,3,7,3,-1);
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
    _pStringBoard02->_pFader->behave();
}

GameBeginningScene::~GameBeginningScene() {
}
