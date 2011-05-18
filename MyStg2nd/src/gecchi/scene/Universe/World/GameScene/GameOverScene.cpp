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
    blindScene();
    _pStringBoard01->update("");
    _pPrg->change(GAMEOVER_SCENE_PROG_INIT);
}
void GameOverScene::initialize() {
    _TRACE_("GameOverScene::initialize()");
}

void GameOverScene::processBehavior() {

    switch (_pPrg->getChangeFrom()) {
        case GAMEOVER_SCENE_PROG_DISP: {
            fadeoutScene(FADE_FRAME);
            inactivateDelay(FADE_FRAME);
            break;
        }

        default:
            break;
    }


    switch (_pPrg->get()) {
        case GAMEOVER_SCENE_PROG_INIT: {
            _pPrg->change(GAMEOVER_SCENE_PROG_DISP);
            break;
        }

        case GAMEOVER_SCENE_PROG_DISP: {
            if (_pPrg->isJustChanged()) {
                _pStringBoard01->update(500, 500, "GAME OVER (-_-;)");
                fadeinScene(FADE_FRAME);
            }
            if (VB->isPushedDown(VB_UI_EXECUTE) || _pPrg->getFrameInProgress() == 420) {
                throwEventToUpperTree(EVENT_GAME_OVER_FINISH);
                _pPrg->change(GAMEOVER_SCENE_PROG_FINISH);
            }
            break;
        }

        case GAMEOVER_SCENE_PROG_FINISH: {
            if (_pPrg->isJustChanged()) {
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
