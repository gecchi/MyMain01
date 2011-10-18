#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

enum {
    GAMEBEGINNINGSCENE_PROG_INIT = 1   ,
    GAMEBEGINNINGSCENE_PROG_SELECT_MODE,
    GAMEBEGINNINGSCENE_PROG_DECIDE     ,
    GAMEBEGINNINGSCENE_PROG_FINISH     ,
};

GameBeginningScene::GameBeginningScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "GameBeginningScene";

    _pStringBoard01 = NEW LabelGecchi16Font("STR01");
    getDirector()->addSubGroup(KIND_EFFECT, _pStringBoard01);
    _pStringBoard02 = NEW LabelGecchi16Font("STR02");
    getDirector()->addSubGroup(KIND_EFFECT, _pStringBoard02);
    _selected_stage = 0;
    useProgress(GAMEBEGINNINGSCENE_PROG_FINISH);
}

void GameBeginningScene::onReset() {
    _TRACE_("GameBeginningScene::onReset()");
    _pProg->change(GAMEBEGINNINGSCENE_PROG_INIT);
//    fadeinScene(0);
    _pStringBoard01->update("");
    _pStringBoard02->update("");
    _pStringBoard02->_pFader->stopImmediately();
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
        case GAMEBEGINNINGSCENE_PROG_INIT: {
            _pProg->change(GAMEBEGINNINGSCENE_PROG_SELECT_MODE);
            break;
        }

        case GAMEBEGINNINGSCENE_PROG_SELECT_MODE: {
            if (_pProg->isJustChanged()) {
                _pStringBoard01->update(Px2Co(200), Px2Co(200), "GAME_BEGINNING_SCENE BEGIN");
                _pStringBoard02->update(Px2Co(200), Px2Co(250), "SELECT MODE!");
            }
            if (_pProg->get() == GAMEBEGINNINGSCENE_PROG_SELECT_MODE) {
                if (VB->isPushedDown(VB_UI_EXECUTE) || _pProg->getFrameInProgress() == 300) {
                    _pProg->change(GAMEBEGINNINGSCENE_PROG_DECIDE);
                }
            }
            break;
        }

        case GAMEBEGINNINGSCENE_PROG_DECIDE: {
            if (_pProg->isJustChanged()) {
                _pStringBoard02->update(Px2Co(300), Px2Co(300), "OK OK OK");
                _pStringBoard02->_pFader->beat(20,3,7,3,-1);
//                fadeoutScene(FADE_FRAMES);
            }
            if (_pProg->getFrameInProgress() == 20) {
                throwEventToUpperTree(EVENT_GAMEMODE_DECIDE);
            }

//
//            if (_pProg->getFrameInProgress() == FADE_FRAMES) {
//                _pProg->change(GAMEBEGINNINGSCENE_PROG_FINISH);
//            }
            break;
        }

        case GAMEBEGINNINGSCENE_PROG_FINISH: {
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

void GameBeginningScene::processFinal() {
}

GameBeginningScene::~GameBeginningScene() {
}
