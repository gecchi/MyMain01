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
    //changeProgress(GAMEENDING_SCENE_PROG_INIT);
}
void GameOverScene::ready() {
    _TRACE_("GameOverScene::ready()");
}
void GameOverScene::initialize() {
    _TRACE_("GameOverScene::initialize()");
}

void GameOverScene::processBehavior() {
    if (getActivePartFrame() == 10) {
        _pStringBoard01->update(100, 100, "GAME OVER");
    }

    if (VB->isPushedDown(VB_UI_EXECUTE)) { //VB_UI_EXECUTE‚Åƒ^ƒCƒgƒ‹‚Ö
        throwEventToUpperTree(EVENT_GAME_OVER_FINISH);
        inactivateDelay(120);
    }

}

void GameOverScene::processFinal() {
}

GameOverScene::~GameOverScene() {
}
