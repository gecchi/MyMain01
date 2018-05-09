#include "HgrWorld.h"

#include "jp/ggaf/core/util/GgafLinearQuadtree.h"
#include "jp/ggaf/dxcore/util/GgafDxInput.h"
#include "scene/HgrSpacetime/HgrWorld/TrialAndErrScene.h"
#include "scene/HgrSpacetime.h"
#include "HgrGod.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace Hogera;

HgrWorld::HgrWorld(const char* prm_name) : GgafLib::DefaultScene(prm_name) {
    vb_.remap(VB_UP     , VBK_UP   , VBJ_Y_POS_MINUS);  //VB_UP      = �L�[�{�[�h�� �܂��́AY���| �Ƃ���B
    vb_.remap(VB_DOWN   , VBK_DOWN , VBJ_Y_POS_PLUS );  //VB_DOWN    = �L�[�{�[�h�� �܂��́AY���{ �Ƃ���B
    vb_.remap(VB_LEFT   , VBK_LEFT , VBJ_X_POS_MINUS);  //VB_LEFT    = �L�[�{�[�h�� �܂��́AX���| �Ƃ���B
    vb_.remap(VB_RIGHT  , VBK_RIGHT, VBJ_X_POS_PLUS );  //VB_RIGHT   = �L�[�{�[�h�� �܂��́AX���{ �Ƃ���B
    vb_.remap(VB_BUTTON1, VBK_SPACE, VBJ_BUTTON_01  );  //VB_BUTTON1 = �X�y�[�X�L�[ �܂��� �W���C�X�e�B�b�N�{�^���P �Ƃ���B
    vb_.remapK(VB_UI_DEBUG, VBK_Q);

    pTrialAndErrScene_ = nullptr;
    pHitCheckRounder_  = P_GOD->getSpacetime()->getLinearQuadtreeHitCheckRounder();
}

void HgrWorld::initialize() {
    pTrialAndErrScene_ = desireActor(TrialAndErrScene);
    addSubLast(pTrialAndErrScene_);
}

void HgrWorld::processBehavior() {
    vb_.update(); //���͏󋵍X�V
}

void HgrWorld::processJudgement() {
    //�����蔻��`�F�b�N
    if (GgafDxInput::isPushedDownKey(DIK_I)) {
        _TRACE_("----------------------------------");
        P_GOD->getSpacetime()->getLinearQuadtree()->putTree();
        _TRACE_("----------------------------------");
    }
    pHitCheckRounder_->executeAll(HGR_MIKATA, HGR_TEKI);
    //executeAllHitChk �� processJudgement() �ŌĂԕK�v����
    //(processBehavior())�ł͂܂��o�^����Ă��Ȃ�)
}

HgrWorld::~HgrWorld() {
//    GGAF_DELETE(pBarVal_);
}

