#include "VvWorld.h"

#include "jp/ggaf/core/GgafFactory.h"
#include "jp/ggaf/core/util/GgafLinearQuadtree.h"
#include "jp/ggaf/dxcore/util/GgafDxInput.h"
#include "scene/VvSpacetime/VvWorld/TrialAndErrScene.h"
#include "scene/VvSpacetime.h"
#include "VvGod.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVrain;

VvWorld::VvWorld(const char* prm_name) : GgafLib::DefaultScene(prm_name) {
    vb_.remap(VB_UP     , VBK_UP   , VBJ_Y_POS_MINUS);  //VB_UP      = キーボード↑ または、Y軸－ とする。
    vb_.remap(VB_DOWN   , VBK_DOWN , VBJ_Y_POS_PLUS );  //VB_DOWN    = キーボード↓ または、Y軸＋ とする。
    vb_.remap(VB_LEFT   , VBK_LEFT , VBJ_X_POS_MINUS);  //VB_LEFT    = キーボード← または、X軸－ とする。
    vb_.remap(VB_RIGHT  , VBK_RIGHT, VBJ_X_POS_PLUS );  //VB_RIGHT   = キーボード→ または、X軸＋ とする。
    vb_.remap(VB_BUTTON1, VBK_SPACE, VBJ_BUTTON_01  );  //VB_BUTTON1 = スペースキー または ジョイスティックボタン１ とする。
    vb_.remapK(VB_UI_DEBUG, VBK_Q);

    pTrialAndErrScene_ = nullptr;
    pHitCheckRounder_  = P_GOD->getSpacetime()->getLinearQuadtreeHitCheckRounder();
}

void VvWorld::initialize() {
    pTrialAndErrScene_ = createInFactory(TrialAndErrScene, "TrialAndErrScene");
    addSubLast(pTrialAndErrScene_);
}

void VvWorld::processBehavior() {
    vb_.update(); //入力状況更新
}

void VvWorld::processJudgement() {
    //当たり判定チェック
    if (GgafDxInput::isPushedDownKey(DIK_I)) {
        _TRACE_("----------------------------------");
        P_GOD->getSpacetime()->getLinearQuadtree()->putTree();
        _TRACE_("----------------------------------");
    }
    pHitCheckRounder_->executeAll(VV_MIKATA, VV_TEKI);
    //executeAllHitChk は processJudgement() で呼ぶ必要あり
    //(processBehavior())ではまだ登録されていない)
}

VvWorld::~VvWorld() {
//    GGAF_DELETE(pBarVal_);
}

