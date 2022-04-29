#include "GameEndingScene.h"

#include "jp/gecchi/VioletVreath/actor/VVCommonActorsHeader.h"



using namespace GgafLib;
using namespace VioletVreath;

enum {
    PHASE_INIT    ,
    PHASE_BEGIN   ,
    PHASE_OPE     ,
    PHASE_DECIDE  ,
    PHASE_END     ,
    PHASE_BANPEI,
};

GameEndingScene::GameEndingScene(const char* prm_name) : VvScene<DefaultScene>(prm_name) {
    _class_name = "GameEndingScene";
}

void GameEndingScene::onReset() {
    //pPhase->change(GameEndingScene::PHASE_INIT);
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
