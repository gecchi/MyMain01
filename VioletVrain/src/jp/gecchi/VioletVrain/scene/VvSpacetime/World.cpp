#include "World.h"

#include "jp/ggaf/core/util/GgafLinearQuadtree.h"
#include "jp/ggaf/dxcore/util/GgafDxInput.h"
#include "jp/gecchi/VioletVrain/scene/VvSpacetime/World/TrialAndErrScene.h"
#include "jp/gecchi/VioletVrain/scene/VvSpacetime.h"
#include "jp/gecchi/VioletVrain/VvGod.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVrain;

World::World(const char* prm_name) : GgafLib::DefaultScene(prm_name) {
    vb_.remap(VB_UP     , VBK_UP   , VBJ_Y_POS_MINUS);  //VB_UP      = �L�[�{�[�h�� �܂��́AY���| �Ƃ���B
    vb_.remap(VB_DOWN   , VBK_DOWN , VBJ_Y_POS_PLUS );  //VB_DOWN    = �L�[�{�[�h�� �܂��́AY���{ �Ƃ���B
    vb_.remap(VB_LEFT   , VBK_LEFT , VBJ_X_POS_MINUS);  //VB_LEFT    = �L�[�{�[�h�� �܂��́AX���| �Ƃ���B
    vb_.remap(VB_RIGHT  , VBK_RIGHT, VBJ_X_POS_PLUS );  //VB_RIGHT   = �L�[�{�[�h�� �܂��́AX���{ �Ƃ���B
    vb_.remap(VB_BUTTON1, VBK_SPACE, VBJ_BUTTON_01  );  //VB_BUTTON1 = �X�y�[�X�L�[ �܂��� �W���C�X�e�B�b�N�{�^���P �Ƃ���B
    vb_.remapK(VB_UI_DEBUG, VBK_Q);

    pTrialAndErrScene_ = nullptr;
    pHitCheckRounder_  = P_GOD->getSpacetime()->getLinearQuadtreeHitCheckRounder();
}

void World::initialize() {
    pTrialAndErrScene_ = desireScene(TrialAndErrScene, "TrialAndErrScene");
    addSubLast(pTrialAndErrScene_);
}

void World::processBehavior() {
    vb_.update(); //���͏󋵍X�V
}

void World::processJudgement() {
    //�����蔻��`�F�b�N
    if (GgafDxInput::isPushedDownKey(DIK_I)) {
        _TRACE_("----------------------------------");
        P_GOD->getSpacetime()->getLinearQuadtree()->putTree();
        _TRACE_("----------------------------------");
    }
    pHitCheckRounder_->executeAll(VV_MIKATA, VV_TEKI);
    //executeAllHitChk �� processJudgement() �ŌĂԕK�v����
    //(processBehavior())�ł͂܂��o�^����Ă��Ȃ�)
}

World::~World() {
//    GGAF_DELETE(pBarVal_);
}
