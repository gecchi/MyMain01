#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

bool Stage::_pause = false;

Stage::Stage(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "Stage";
    useProgress(STAGE_PROG_END);
}

void Stage::initialize() {
    _pProg->set(STAGE_PROG_INIT);
}

void Stage::onCatchEvent(hashval prm_no, void* prm_pSource) {
}

Stage::~Stage() {
}
