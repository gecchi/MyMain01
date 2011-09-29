#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;


enum {
    GAMEENDINGSCENE_PROG_INIT = 1,
    GAMEENDINGSCENE_PROG_BEGIN   ,
    GAMEENDINGSCENE_PROG_OPE     ,
    GAMEENDINGSCENE_PROG_DECIDE  ,
    GAMEENDINGSCENE_PROG_END     ,
};

GameEndingScene::GameEndingScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "GameEndingScene";
    useProgress(GAMEENDINGSCENE_PROG_END);
}

void GameEndingScene::onReset() {
    //_pProg->change(GAMEENDINGSCENE_PROG_INIT);
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
