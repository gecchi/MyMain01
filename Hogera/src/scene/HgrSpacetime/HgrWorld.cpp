#include "HgrWorld.h"

#include "jp/ggaf/core/GgafFactory.h"
#include "jp/ggaf/core/util/GgafLinearOctreeForActor.h"
#include "jp/ggaf/lib/util/VirtualButton.h"
#include "jp/ggaf/core/GgafFactory.h"
#include "scene/HgrSpacetime/HgrWorld/TrialAndErrScene.h"
#include "scene/HgrSpacetime.h"
#include "HgrGod.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace Hogera;

HgrWorld::HgrWorld(const char* prm_name) : GgafLib::DefaultScene(prm_name) {
    vb_ = NEW VirtualButton();
    vb_->remapK(VB_UI_DEBUG, VBK_Q     );
    vb_->remapK(VB_PAUSE   , VBK_ESCAPE);
    pTrialAndErrScene_ = nullptr;
}

void HgrWorld::initialize() {
    pTrialAndErrScene_ = createInFactory(TrialAndErrScene, "TrialAndErrScene");
    addSubLast(pTrialAndErrScene_);

}

void HgrWorld::processBehavior() {
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

void HgrWorld::processJudgement() {
    //�����蔻��`�F�b�N
    P_GOD->getSpacetime()->getLinearOctree()->executeAllHitChk(HGR_MIKATA, HGR_TEKI);
    //executeAllHitChk �� processJudgement() �ŌĂԕK�v����
    //(processBehavior())�ł͂܂��o�^����Ă��Ȃ�)
}

HgrWorld::~HgrWorld() {
//    GGAF_DELETE(pBarVal_);
}

