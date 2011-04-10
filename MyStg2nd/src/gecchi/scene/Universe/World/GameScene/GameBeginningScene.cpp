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
    _pPrg->change(GAMEBEGINNING_SCENE_PROG_INIT);
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

    switch (_pPrg->get()) {
        case GAMEBEGINNING_SCENE_PROG_INIT: {
            _pPrg->change(GAMEBEGINNING_SCENE_PROG_SELECT_MODE);
            break;
        }

        case GAMEBEGINNING_SCENE_PROG_SELECT_MODE: {
            if (_pPrg->isJustChanged()) {
                _pStringBoard01->update(200, 200, "GAME_BEGINNING_SCENE BEGIN");
                _pStringBoard02->update(200, 250, "SELECT MODE!");
            }
            if (_pPrg->get() == GAMEBEGINNING_SCENE_PROG_SELECT_MODE) {
                if (VB->isPushedDown(VB_UI_EXECUTE) || _pPrg->getFrameInProgress() == 300) {
                    _pPrg->change(GAMEBEGINNING_SCENE_PROG_DECIDE);
                }
            }
            break;
        }

        case GAMEBEGINNING_SCENE_PROG_DECIDE: {
            if (_pPrg->isJustChanged()) {
                fadeoutScene(FADE_FRAME);
                throwEventToUpperTree(EVENT_GAMEMODE_DECIDE);
            }
            if (_pPrg->getFrameInProgress() % 10 < 5 ) {
                _pStringBoard02->update(400, 500, "OK OK OK");
            } else {
                _pStringBoard02->update(400, 500, "");
            }
            if (_pPrg->getFrameInProgress() == FADE_FRAME) {
                _pPrg->change(GAMEBEGINNING_SCENE_PROG_FINISH);
            }
            break;
        }

        case GAMEBEGINNING_SCENE_PROG_FINISH: {
            if (_pPrg->isJustChanged()) {
                inactivate();
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
