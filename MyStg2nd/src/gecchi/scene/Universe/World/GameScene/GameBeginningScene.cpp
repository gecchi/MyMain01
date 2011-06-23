#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

GameBeginningScene::GameBeginningScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "GameBeginningScene";

    _pStringBoard01 = NEW LabelGecchi16Font("STR01");
    getLordActor()->addSubGroup(KIND_EFFECT, _pStringBoard01);
    _pStringBoard02 = NEW LabelGecchi16Font("STR02");
    getLordActor()->addSubGroup(KIND_EFFECT, _pStringBoard02);
    _selected_stage = 0;
    useProgress(10);
}


void GameBeginningScene::onReset() {
    _TRACE_("GamePreTitleScene::onReset()");
    _pProg->change(GAMEBEGINNINGSCENE_PROG_INIT);
    unblindScene();
    _pStringBoard01->update("");
    _pStringBoard02->update("");
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
                _pStringBoard01->update(200*1000, 200*1000, "GAME_BEGINNING_SCENE BEGIN");
                _pStringBoard02->update(200*1000, 250*1000, "SELECT MODE!");
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
                fadeoutScene(FADE_FRAME);
                throwEventToUpperTree(EVENT_GAMEMODE_DECIDE);
            }
            if (_pProg->getFrameInProgress() % 10 < 5 ) {
                _pStringBoard02->update(400*1000, 500*1000, "OK OK OK");
            } else {
                _pStringBoard02->update(400*1000, 500*1000, "");
            }
            if (_pProg->getFrameInProgress() == FADE_FRAME) {
                _pProg->change(GAMEBEGINNINGSCENE_PROG_FINISH);
            }
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

}

void GameBeginningScene::processFinal() {
}

GameBeginningScene::~GameBeginningScene() {
}
