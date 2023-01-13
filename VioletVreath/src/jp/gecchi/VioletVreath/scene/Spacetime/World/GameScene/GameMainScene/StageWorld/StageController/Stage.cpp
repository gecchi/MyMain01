#include "Stage.h"

#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"



using namespace GgafLib;
using namespace VioletVreath;

bool Stage::pause_ = false;

Stage::Stage(const char* prm_name) : VvScene<DefaultScene>(prm_name) {
    _class_name = "Stage";
    pScene_StagePartCtrler_ = nullptr;
}

void Stage::initialize() {
    getPhase()->reset(PHASE_INIT);
}
void Stage::processBehavior() {
    DefaultScene::processBehavior();
    ScenePhase* pPhase = getPhase();
    switch (pPhase->getCurrent()) {
        case PHASE_BEGIN: {
            if (pPhase->hasJustChanged()) {
                //乱数シード更新
                uint32_t seed = (uint32_t)G_RANK_DISP;
                _TRACE_(FUNC_NAME<<" 乱数シード更新 changeSeed("+XTOS(seed)+")");
                GgafCore::CmRandomNumberGenerator::getInstance()->changeSeed(seed);
            }
            break;
        }
        default: {
            break;
        }

    }
}
void Stage::onCatchEvent(eventval prm_event_val, void* prm_pSource) {
}

Stage::~Stage() {
}
