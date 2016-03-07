#include "GameEndingScene.h"

#include "jp/gecchi/VioletVreath/actor/VVCommonActorsHeader.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

GameEndingScene::GameEndingScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "GameEndingScene";
    useProgress(GameEndingScene::PROG_BANPEI-1);
}

void GameEndingScene::onReset() {
    //pProg->change(GameEndingScene::PROG_INIT);
}
void GameEndingScene::ready() {
    _TRACE_(FUNC_NAME<<"");
}

void GameEndingScene::initialize() {
    _TRACE_(FUNC_NAME<<"");
}

void GameEndingScene::processBehavior() {
}

GameEndingScene::~GameEndingScene() {
}
