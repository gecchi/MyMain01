#include "MgrWorld.h"

#include "jp/ggaf/core/actor/SceneMediator.h"
#include "jp/ggaf/lib/util/VirtualButton.h"
#include "scene/MgrSpacetime/MgrWorld/TrialAndErrScene.h"
#include "scene/MgrSpacetime/MgrWorld/ParallelCurveTestScene.h"
#include "scene/MgrSpacetime/MgrWorld/TestScene.h"
#include "scene/MgrSpacetime.h"
#include "actor/PointerTest.h"
#include "MgrCaretaker.h"

using namespace GgafLib;
using namespace Mogera;

MgrWorld::MgrWorld(const char* prm_name) : GgafLib::DefaultScene(prm_name) {
    pTestScene_ = nullptr;
    pPointerTest_ = nullptr;
    pTrialAndErrScene_ = nullptr;
//    pHitCheckRounder_ = pCARETAKER->getSpacetime()->getLinearOctreeHitCheckRounder();
//    pHitCheckRounder_b_ = pCARETAKER->getSpacetime()->getLinearQuadtreeHitCheckRounder_b();
}

void MgrWorld::initialize() {
//    pTestScene_ = desireScene(TestScene);
//    appendChild(pTestScene_);
    pPointerTest_ = desireActor(PointerTest);
    pPointerTest_->setPosition(PX_C(300), PX_C(100));
    bringSceneMediator()->appendGroupChild(MGR_TEKI, pPointerTest_);
    pTrialAndErrScene_ = desireScene(TrialAndErrScene);
    appendChild(pTrialAndErrScene_);
}

void MgrWorld::processBehavior() {
    VirtualButton* pVb = pCARETAKER->getSpacetime()->pVb_;
    //ワイヤフレーム表示切替
    if (pVb->isPushedDown(0, VB_UI_DEBUG)) {
        if (pCARETAKER->_d3dfillmode == D3DFILL_WIREFRAME) {
            pCARETAKER->_d3dfillmode = D3DFILL_SOLID;
        } else {
            pCARETAKER->_d3dfillmode = D3DFILL_WIREFRAME;
        }
    }

    //一時停止
    if (pVb->isPushedDown(0, VB_PAUSE)) {
        if (pTestScene_->wasPaused()) {
            pTestScene_->unpause();
        } else {
            pTestScene_->pause();
        }
    }
}

void MgrWorld::processJudgement() {
    //当たり判定チェック

//    pHitCheckRounder_->executeAll(MGR_MIKATA, MGR_TEKI);
//
//    pHitCheckRounder_b_->executeAll(MGR_MIKATA, MGR_TEKI);

}

MgrWorld::~MgrWorld() {
//    GGAF_DELETE(pBarVal_);
}

