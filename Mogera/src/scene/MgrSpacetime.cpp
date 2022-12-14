#include "MgrSpacetime.h"

#include "jp/ggaf/core/actor/SceneMediator.h"
#include "jp/ggaf/core/scene/Scene.h"
#include "jp/ggaf/lib/util/VirtualButton.h"

#include "actor/camera/MgrCameraWorker.h"
#include "actor/PointerTest.h"
#include "MgrCaretaker.h"
#include "scene/MgrSpacetime/MgrWorld.h"
#include "util/MgrUtil.h"

using namespace GgafCore;
using namespace GgafDx;
using namespace GgafLib;
using namespace Mogera;

#define PRIMARY_VIEW 0
#define SECONDARY_VIEW 1

MgrSpacetime::MgrSpacetime(const char* prm_name, MgrCamera* prm_pCam) :
        GgafLib::DefaultSpacetime(prm_name, prm_pCam) {
    pWorld_ = nullptr;
    UTIL::left_top_x_ = CONFIG::DUAL_VIEW ? PX_C(pCARETAKER->_aRect_HarfRenderTargetBuffer[PRIMARY_VIEW].left) :
                                            PX_C(pCARETAKER->_rectRenderTargetBuffer.left);
    UTIL::left_top_y_ = CONFIG::DUAL_VIEW ? PX_C(pCARETAKER->_aRect_HarfRenderTargetBuffer[PRIMARY_VIEW].top) :
                                            PX_C(pCARETAKER->_rectRenderTargetBuffer.top);
    UTIL::center_x_ = PX_C(CONFIG::RENDER_TARGET_BUFFER_WIDTH / 2);
    UTIL::center_y_ = PX_C(CONFIG::RENDER_TARGET_BUFFER_HEIGHT / 2);

    pActiveCamWorker_ = NEW MgrCameraWorker("MgrCameraWorker", prm_pCam);
    bringSceneMediator()->appendGroupChild(pActiveCamWorker_); //基底デフォルトカメラワーク

    pVb_ = NEW VirtualButton();
    pVb_->remapK(VB_UI_DEBUG, VBK_Q     );
    pVb_->remapK(VB_PAUSE   , VBK_ESCAPE);
    pVb_->remap(VB_UP     , VBK_UP   , VBJ_Y_POS_MINUS);  //VB_UP      = キーボード↑ または、Y軸－ とする。
    pVb_->remap(VB_DOWN   , VBK_DOWN , VBJ_Y_POS_PLUS );  //VB_DOWN    = キーボード↓ または、Y軸＋ とする。
    pVb_->remap(VB_LEFT   , VBK_LEFT , VBJ_X_POS_MINUS);  //VB_LEFT    = キーボード← または、X軸－ とする。
    pVb_->remap(VB_RIGHT  , VBK_RIGHT, VBJ_X_POS_PLUS );  //VB_RIGHT   = キーボード→ または、X軸＋ とする。
    pVb_->remap(VB_BUTTON1, VBK_SPACE, VBJ_BUTTON_01  );  //VB_BUTTON1 = スペースキー または ジョイスティックボタン１ とする。
    _TRACE_("Spacetime Bound = X("<<_x_bound_left<<" ~ "<<_x_bound_right<<") Y("<<_y_bound_bottom<<" ~ "<<_y_bound_top<<") Z("<<_z_bound_near<<" ~ "<<_z_bound_far<<")");
}

void MgrSpacetime::initialize() {
    //世界シーン生成し、自シーンの配下に所属させる
    pWorld_ = desireScene(Mogera::MgrWorld);
    appendChild(pWorld_);
}

void MgrSpacetime::processBehavior() {
    pVb_->update(); //入力状況更新

//    bool b1 = pVb_->isPressed(VB_UP);
//    bool b2 = pVb_->wasPressedAtLeastOnce(VB_UP, 10);
//    bool b3 = pVb_->wasPressedAtLeastOnce(VB_UP, 3);
//    _TRACE_(getBehaveingFrame() <<":"<<b1<<":"<<b2<<":"<<b3);
    bool b1 = pVb_->arePushedDownAtOnce(VB_LEFT, VB_UP, VB_RIGHT, 1);
//    bool b2 = pVb_->arePushedDownAtOnce(VB_LEFT, VB_UP, VB_RIGHT, 10);
//    bool b3 = pVb_->arePushedDownAtOnce(VB_LEFT, VB_UP, VB_RIGHT, 60);
//    _TRACE_(getBehaveingFrame() <<":"<<b1<<":"<<b2<<":"<<b3);
    if (b1) {
        _TRACE_(getBehaveingFrame() <<":"<<b1);
    }

}
void MgrSpacetime::processJudgement() {
    //当たり判定チェック
    executeWorldHitCheck(MGR_MIKATA, MGR_TEKI);
    executeViewHitCheck(MGR_MIKATA, MGR_TEKI);
}


MgrSpacetime::~MgrSpacetime() {
    GGAF_DELETE(pVb_);
}

