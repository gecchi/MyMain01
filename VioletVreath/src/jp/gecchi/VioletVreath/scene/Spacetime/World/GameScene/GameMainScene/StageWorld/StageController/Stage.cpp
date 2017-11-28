#include "Stage.h"

#include "jp/ggaf/core/GgafFactory.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

bool Stage::pause_ = false;

Stage::Stage(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "Stage";
    pScene_StagePartCtrler_ = nullptr;
    useProgress(PROG_BANPEI);
}

void Stage::initialize() {
    getProgress()->reset(PROG_INIT);
}
void Stage::processBehavior() {
    DefaultScene::processBehavior();
    SceneProgress* pProg = getProgress();
    switch (pProg->get()) {
        case PROG_BEGIN: {
            if (pProg->hasJustChanged()) {
                //乱数シード更新
                uint32_t seed = (uint32_t)G_RANK_DISP;
                _TRACE_(FUNC_NAME<<" 乱数シード更新 changeSeed("+XTOS(seed)+")");
                CmRandomNumberGenerator::getInstance()->changeSeed(seed);
            }
            break;
        }
        default: {
            break;
        }

    }
}
void Stage::onCatchEvent(hashval prm_no, void* prm_pSource) {
}

Stage::~Stage() {
}
