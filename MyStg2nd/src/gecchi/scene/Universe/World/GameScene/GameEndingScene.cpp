#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

GameEndingScene::GameEndingScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "GameEndingScene";
    useProgress(10);
}

void GameEndingScene::reset() {
    //_pProgress->change(GAMEENDING_SCENE_PROG_INIT);
}
void GameEndingScene::ready() {
    _TRACE_("GameEndingScene::ready()");
}
void GameEndingScene::initialize() {
    _TRACE_("GameEndingScene::initialize()");
}

void GameEndingScene::processBehavior() {
}

void GameEndingScene::processFinal() {
}

GameEndingScene::~GameEndingScene() {
}
