#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

bool Stage::pause_ = false;

Stage::Stage(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "Stage";
    useProgress(Stage::PROG_END);
}

void Stage::initialize() {
    _pProg->set(Stage::PROG_INIT);
}

void Stage::onCatchEvent(hashval prm_no, void* prm_pSource) {
}

Stage::~Stage() {
}
