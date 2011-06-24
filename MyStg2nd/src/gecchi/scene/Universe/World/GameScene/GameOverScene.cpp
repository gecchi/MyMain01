#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

GameOverScene::GameOverScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "GameOverScene";
    _pStringBoard01 = NEW LabelGecchi16Font("STR01");
    getLordActor()->addSubGroup(_pStringBoard01);
    useProgress(10);
}

void GameOverScene::onReset() {
    fadeoutScene(0);
    _pStringBoard01->update("");
    _pProg->change(GAMEOVERSCENE_PROG_INIT);
}
void GameOverScene::initialize() {
    _TRACE_("GameOverScene::initialize()");
}

void GameOverScene::processBehavior() {

    switch (_pProg->getPrev_WhenJustChanged()) {
        case GAMEOVERSCENE_PROG_DISP: {
            fadeoutScene(FADE_FRAME);
            inactivateDelay(FADE_FRAME);
            break;
        }

        default:
            break;
    }


    switch (_pProg->get()) {
        case GAMEOVERSCENE_PROG_INIT: {
            _pProg->change(GAMEOVERSCENE_PROG_DISP);
            break;
        }

        case GAMEOVERSCENE_PROG_DISP: {
            if (_pProg->isJustChanged()) {
                _pStringBoard01->update(500*1000, 500*1000, "GAME OVER (-_-;)");
                fadeinScene(FADE_FRAME);
            }
            if (VB->isPushedDown(VB_UI_EXECUTE) || _pProg->getFrameInProgress() == 420) {
                throwEventToUpperTree(EVENT_GAME_OVER_FINISH);
                _pProg->change(GAMEOVERSCENE_PROG_FINISH);
            }
            break;
        }

        case GAMEOVERSCENE_PROG_FINISH: {
            if (_pProg->isJustChanged()) {
            }
            break;
        }

        default:
            break;
     }
}

void GameOverScene::processFinal() {
}

GameOverScene::~GameOverScene() {
}
