#include "MgrWorld.h"

#include "jp/ggaf/lib/util/VirtualButton.h"
#include "scene/MgrSpacetime/MgrWorld/TrialAndErrScene.h"
#include "scene/MgrSpacetime/MgrWorld/ParallelCurveTestScene.h"
#include "scene/MgrSpacetime/MgrWorld/TestScene.h"
#include "scene/MgrSpacetime.h"
#include "MgrGod.h"

using namespace GgafLib;
using namespace Mogera;

MgrWorld::MgrWorld(const char* prm_name) : GgafLib::DefaultScene(prm_name) {
    pTestScene_ = nullptr;
    pTrialAndErrScene_ = nullptr;
    pHitCheckRounder_ = P_GOD->getSpacetime()->getLinearOctreeHitCheckRounder();
}

void MgrWorld::initialize() {
//    pTestScene_ = desireScene(TestScene);
//    appendChild(pTestScene_);

    pTrialAndErrScene_ = desireScene(TrialAndErrScene);
    appendChild(pTrialAndErrScene_);
}

void MgrWorld::processBehavior() {
    VirtualButton* pVb = P_GOD->getSpacetime()->pVb_;
    //ワイヤフレーム表示切替
    if (pVb->isPushedDown(VB_UI_DEBUG)) {
        if (pGOD->_d3dfillmode == D3DFILL_WIREFRAME) {
            pGOD->_d3dfillmode = D3DFILL_SOLID;
        } else {
            pGOD->_d3dfillmode = D3DFILL_WIREFRAME;
        }
    }

    //一時停止
    if (pVb->isPushedDown(VB_PAUSE)) {
        if (pTestScene_->wasPaused()) {
            pTestScene_->unpause();
        } else {
            pTestScene_->pause();
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

