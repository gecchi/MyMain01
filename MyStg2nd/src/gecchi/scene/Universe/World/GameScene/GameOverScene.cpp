#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

GameOverScene::GameOverScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "GameOverScene";
}

void GameOverScene::reset() {
    //changeProgress(GAMEENDING_PROG_INIT);
}
void GameOverScene::ready() {
    _TRACE_("GameOverScene::ready()");
}
void GameOverScene::initialize() {
    _TRACE_("GameOverScene::initialize()");
}

void GameOverScene::processBehavior() {
}

void GameOverScene::processFinal() {
}

GameOverScene::~GameOverScene() {
}
