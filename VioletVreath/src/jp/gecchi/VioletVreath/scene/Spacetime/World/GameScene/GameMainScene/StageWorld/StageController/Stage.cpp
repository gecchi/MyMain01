#include "Stage.h"

#include "jp/gecchi/VioletVreath/God.h"
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
    switch (pPhase->get()) {
        case PHASE_BEGIN: {
            if (pPhase->hasJustChanged()) {
                //�����V�[�h�X�V
                uint32_t seed = (uint32_t)G_RANK_DISP;
                _TRACE_(FUNC_NAME<<" �����V�[�h�X�V changeSeed("+XTOS(seed)+")");
                GgafCore::CmRandomNumberGenerator::getInstance()->changeSeed(seed);
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
