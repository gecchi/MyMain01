#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

GameEndingScene::GameEndingScene(const char* prm_name) : DefaultScene(prm_name) {
}

void GameEndingScene::reset() {
    //setProgress(GAMEENDING_PROG_INIT);
}
void GameEndingScene::ready() {
    //_TRACE_("GameEndingScene::ready()");
}
void GameEndingScene::initialize() {
}

void GameEndingScene::processBehavior() {
}

void GameEndingScene::processFinal() {
}

GameEndingScene::~GameEndingScene() {
}
