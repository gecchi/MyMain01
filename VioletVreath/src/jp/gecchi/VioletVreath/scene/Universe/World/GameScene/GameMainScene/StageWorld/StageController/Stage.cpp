#include "stdafx.h"
#include "Stage.h"

#include "jp/ggaf/core/GgafFactory.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

bool Stage::pause_ = false;

Stage::Stage(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "Stage";
    pScene_StagePartCtrler_ = nullptr;
    useProgress(Stage::_BANPEI_-1);
}

void Stage::initialize() {
    _pProg->reset(Stage::PROG_INIT);
    CmRandomNumberGenerator::getInstance()->changeSeed(P_MYSHIP->_X + P_MYSHIP->_Y + P_MYSHIP->_Z);
}

void Stage::onCatchEvent(hashval prm_no, void* prm_pSource) {
}

Stage::~Stage() {
}
