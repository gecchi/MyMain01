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
    //�L�������{�^�����͂ňړ�
    vb_->update(); //���͏󋵍X�V
    //���C���t���[���\���ؑ�
    if (vb_->isPushedDown(VB_UI_DEBUG)) {
        if (GgafDxGod::_d3dfillmode == D3DFILL_WIREFRAME) {
            GgafDxGod::_d3dfillmode = D3DFILL_SOLID;
        } else {
            GgafDxGod::_d3dfillmode = D3DFILL_WIREFRAME;
        }
    }

    //�ꎞ��~
    if (vb_->isPushedDown(VB_PAUSE)) {
        if (pTrialAndErrScene_->wasPaused()) {
            pTrialAndErrScene_->unpause();
        } else {
            pTrialAndErrScene_->pause();
        }
    }

}

void MgrWorld::processJudgement() {
    //�����蔻��`�F�b�N
    P_GOD->getUniverse()->getLinearOctree()->executeAllHitChk(MGR_MIKATA, MGR_TEKI);
    //executeAllHitChk �� processJudgement() �ŌĂԕK�v����
    //(processBehavior())�ł͂܂��o�^����Ă��Ȃ�)
}

MgrWorld::~MgrWorld() {
//    GGAF_DELETE(pBarVal_);
}

