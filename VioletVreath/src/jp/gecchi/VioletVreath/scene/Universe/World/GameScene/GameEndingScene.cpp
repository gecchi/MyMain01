#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;




GameEndingScene::GameEndingScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "GameEndingScene";
    useProgress(GameEndingScene::PROG_END);
}

void GameEndingScene::onReset() {
    //_pProg->change(GameEndingScene::PROG_INIT);
}
void GameEndingScene::ready() {
    _TRACE_("GameEndingScene::ready()");
}

void GameEndingScene::initialize() {
    _TRACE_("GameEndingScene::initialize()");
}

void GameEndingScene::processBehavior() {
}

GameEndingScene::~GameEndingScene() {
}