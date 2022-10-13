#include "HgrWorld.h"

#include "jp/ggaf/core/util/LinearQuadtree.h"
#include "jp/ggaf/dx/util/Input.h"
#include "scene/HgrSpacetime/HgrWorld/TrialAndErrScene.h"
#include "scene/HgrSpacetime.h"
#include "HgrCaretaker.h"



using namespace GgafLib;
using namespace Hogera;

HgrWorld::HgrWorld(const char* prm_name) : GgafLib::DefaultScene(prm_name) {
    vb_.remap(VB_UP     , VBK_UP   , VBJ_Y_POS_MINUS);  //VB_UP      = キーボード↑ または、Y軸− とする。
    vb_.remap(VB_DOWN   , VBK_DOWN , VBJ_Y_POS_PLUS );  //VB_DOWN    = キーボード↓ または、Y軸＋ とする。
    vb_.remap(VB_LEFT   , VBK_LEFT , VBJ_X_POS_MINUS);  //VB_LEFT    = キーボード← または、X軸− とする。
    vb_.remap(VB_RIGHT  , VBK_RIGHT, VBJ_X_POS_PLUS );  //VB_RIGHT   = キーボード→ または、X軸＋ とする。
    vb_.remap(VB_BUTTON1, VBK_SPACE, VBJ_BUTTON_01  );  //VB_BUTTON1 = スペースキー または ジョイスティックボタン１ とする。
    vb_.remapK(VB_UI_DEBUG, VBK_Q);

    pTrialAndErrScene_ = nullptr;
    pHitCheckRounder_  = pCARETAKER->getSpacetime()->getLinearQuadtreeHitCheckRounder();
}

void HgrWorld::initialize() {
    pTrialAndErrScene_ = desireActor(TrialAndErrScene);
    appendChild(pTrialAndErrScene_);
}

void HgrWorld::processBehavior() {
    vb_.update(); //入力状況更新
}

void HgrWorld::processJudgement() {
    //当たり判定チェック
    if (GgafDx::Input::isPushedDownKey(DIK_I)) {
        _TRACE_("----------------------------------");
        pCARETAKER->getSpacetime()->getLinearQuadtree()->putTree();
        _TRACE_("----------------------------------");
    }
    pHitCheckRounder_->executeAll(HGR_MIKATA, HGR_TEKI);
    //executeAllHitChk は processJudgement() で呼ぶ必要あり
    //(processBehavior())ではまだ登録されていない)
}

HgrWorld::~HgrWorld() {
//    GGAF_DELETE(pBarVal_);
}

