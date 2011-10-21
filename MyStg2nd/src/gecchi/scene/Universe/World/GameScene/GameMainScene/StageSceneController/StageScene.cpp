#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

bool StageScene::_pause = false;

StageScene::StageScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "StageScene";
    useProgress(STAGESCENE_PROG_END);
}

void StageScene::initialize() {
    _pProg->set(STAGESCENE_PROG_INIT);
}

void StageScene::onCatchEvent(UINT32 prm_no, void* prm_pSource) {
}

StageScene::~StageScene() {
}
