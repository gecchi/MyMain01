#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

GameOverScene::GameOverScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "GameOverScene";
    _pStringBoard01 = NEW LabelGecchi16Font("STR01");
    getDirector()->addSubGroup(_pStringBoard01);
    useProgress(10);
}

void GameOverScene::onReset() {
    fadeoutScene(0);
    _pStringBoard01->update("");
    _pProg->change(GameOverScene::PROG_INIT);
}
void GameOverScene::initialize() {
    _TRACE_("GameOverScene::initialize()");
}

void GameOverScene::processBehavior() {

    switch (_pProg->getPrev_WhenJustChanged()) {
        case GameOverScene::PROG_DISP: {
            fadeoutScene(FADE_FRAMES);
            inactivateDelay(FADE_FRAMES);
            break;
        }

        default:
            break;
    }


    switch (_pProg->get()) {
        case GameOverScene::PROG_INIT: {
            _pProg->change(GameOverScene::PROG_DISP);
            break;
        }

        case GameOverScene::PROG_DISP: {
            if (_pProg->isJustChanged()) {
                _pStringBoard01->update(500*1000, 500*1000, "GAME OVER (-_-;)");
                fadeinScene(FADE_FRAMES);
            }
            if (VB->isPushedDown(VB_UI_EXECUTE) || _pProg->getFrameInProgress() == 420) {
                throwEventToUpperTree(EVENT_GAME_OVER_FINISH);
                _pProg->change(GameOverScene::PROG_FINISH);
            }
            break;
        }

        case GameOverScene::PROG_FINISH: {
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
