#include "MgrWorld.h"

#include "jp/ggaf/core/GgafFactory.h"
#include "jp/ggaf/lib/util/LinearOctreeForActor.h"
#include "jp/ggaf/lib/util/VirtualButton.h"
#include "jp/ggaf/core/GgafFactory.h"
#include "scene/MgrUniverse/MgrWorld/TrialAndErrScene.h"
#include "scene/MgrUniverse.h"
#include "MgrGod.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace Mogera;

MgrWorld::MgrWorld(const char* prm_name) : GgafLib::DefaultScene(prm_name) {
    vb_ = NEW VirtualButton();
    vb_->remap_VB_UI_DEBUG(VBK_Q);
    vb_->remap_VB_PAUSE(VBK_ESCAPE);
    pTrialAndErrScene_ = nullptr;
}

void MgrWorld::initialize() {
    pTrialAndErrScene_ = createInFactory(TrialAndErrScene, "TrialAndErrScene");
    addSubLast(pTrialAndErrScene_);
}

void MgrWorld::processBehavior() {
    //キャラをボタン入力で移動
    vb_->update(); //入力状況更新
    //ワイヤフレーム表示切替
    if (vb_->isPushedDown(VB_UI_DEBUG)) {
        if (GgafDxGod::_d3dfillmode == D3DFILL_WIREFRAME) {
            GgafDxGod::_d3dfillmode = D3DFILL_SOLID;
        } else {
            GgafDxGod::_d3dfillmode = D3DFILL_WIREFRAME;
        }
    }

    //一時停止
    if (vb_->isPushedDown(VB_PAUSE)) {
        if (pTrialAndErrScene_->wasPaused()) {
            pTrialAndErrScene_->unpause();
        } else {
            pTrialAndErrScene_->pause();
        }
    }

}

void MgrWorld::processJudgement() {
    //当たり判定チェック
    P_GOD->getUniverse()->getLinearOctree()->executeAllHitChk(MGR_MIKATA, MGR_TEKI);
    //executeAllHitChk は processJudgement() で呼ぶ必要あり
    //(processBehavior())ではまだ登録されていない)
}

MgrWorld::~MgrWorld() {
//    GGAF_DELETE(pBarVal_);
}

