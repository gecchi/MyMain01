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
}

void GameOverScene::reset() {
    blindScene();
    _pStringBoard01->update("");
    changeProgress(GAMEOVER_SCENE_PROG_INIT);
}
void GameOverScene::initialize() {
    _TRACE_("GameOverScene::initialize()");
    reset();
}

void GameOverScene::processBehavior() {
    //GAMEOVER_SCENE_PROG_INIT éûÇÃèàóù
    if (getProgress() == GAMEOVER_SCENE_PROG_INIT) {
        changeProgress(GAMEOVER_SCENE_PROG_DISP);
    }

    //GAMEOVER_SCENE_PROG_DISP éûÇÃèàóù
    if (onActiveProgress(GAMEOVER_SCENE_PROG_DISP)) {
        _TRACE_("GameOverScene onActiveProgress(GAMEOVER_SCENE_PROG_DISP)");
        _pStringBoard01->update(500, 500, "GAME OVER (-_-;)");
        fadeinScene(FADE_FRAME);
    }
    if (getProgress() == GAMEOVER_SCENE_PROG_DISP) {
        if (VB->isPushedDown(VB_UI_EXECUTE) || getActivePartFrameInProgress() == 300) {
            throwEventToUpperTree(EVENT_GAME_OVER_FINISH);
            changeProgress(GAMEOVER_SCENE_PROG_FINISH);
        }
    }
    if (onInactiveProgress(GAMEOVER_SCENE_PROG_DISP)) {
        fadeoutScene(FADE_FRAME);
        inactivateDelay(FADE_FRAME);
        _TRACE_("GameOverScene onInactiveProgress(GAMEOVER_SCENE_PROG_DISP)");
    }

    //GAMEOVER_SCENE_PROG_FINISH éûÇÃèàóù
    if (onActiveProgress(GAMEOVER_SCENE_PROG_FINISH)) {
        _TRACE_("GameOverScene onActiveProgress(GAMEOVER_SCENE_PROG_DISP)");
    }
    if (getProgress() == GAMEOVER_SCENE_PROG_FINISH) {
    }
    if (onInactiveProgress(GAMEOVER_SCENE_PROG_FINISH)) {
        _TRACE_("GameOverScene onInactiveProgress(GAMEOVER_SCENE_PROG_FINISH)");
    }

}

void GameOverScene::processFinal() {
}

GameOverScene::~GameOverScene() {
}
