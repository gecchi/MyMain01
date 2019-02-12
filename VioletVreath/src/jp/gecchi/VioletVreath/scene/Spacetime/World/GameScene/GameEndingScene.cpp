#include "GameEndingScene.h"

#include "jp/gecchi/VioletVreath/actor/VVCommonActorsHeader.h"



using namespace GgafLib;
using namespace VioletVreath;

enum {
    PROG_INIT    ,
    PROG_BEGIN   ,
    PROG_OPE     ,
    PROG_DECIDE  ,
    PROG_END     ,
    PROG_BANPEI,
};

GameEndingScene::GameEndingScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "GameEndingScene";
    useProgress(PROG_BANPEI-1);
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
