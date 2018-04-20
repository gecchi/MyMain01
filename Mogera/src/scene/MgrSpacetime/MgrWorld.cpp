#include "MgrWorld.h"

#include "jp/ggaf/lib/util/VirtualButton.h"
#include "scene/MgrSpacetime/MgrWorld/TrialAndErrScene.h"
#include "scene/MgrSpacetime.h"
#include "MgrGod.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace Mogera;

MgrWorld::MgrWorld(const char* prm_name) : GgafLib::DefaultScene(prm_name) {
    pTrialAndErrScene_ = nullptr;

    pHitCheckRounder_ = P_GOD->getSpacetime()->getLinearOctreeHitCheckRounder();
}

void MgrWorld::initialize() {
    pTrialAndErrScene_ = keepWishing(TrialAndErrScene, "TrialAndErrScene");
    addSubLast(pTrialAndErrScene_);

}

void MgrWorld::processBehavior() {
    VirtualButton* pVb = P_GOD->getSpacetime()->pVb_;
    //ワイヤフレーム表示切替
    if (pVb->isPushedDown(VB_UI_DEBUG)) {
        if (GgafDxGod::_d3dfillmode == D3DFILL_WIREFRAME) {
            GgafDxGod::_d3dfillmode = D3DFILL_SOLID;
        } else {
            GgafDxGod::_d3dfillmode = D3DFILL_WIREFRAME;
        }
    }

    //一時停止
    if (pVb->isPushedDown(VB_PAUSE)) {
        if (pTrialAndErrScene_->wasPaused()) {
            pTrialAndErrScene_->unpause();
        } else {
            pTrialAndErrScene_->pause();
        }
    }

}

void MgrWorld::processJudgement() {
    //当たり判定チェック
    pHitCheckRounder_->executeAll(MGR_MIKATA, MGR_TEKI);
}

MgrWorld::~MgrWorld() {
//    GGAF_DELETE(pBarVal_);
}

