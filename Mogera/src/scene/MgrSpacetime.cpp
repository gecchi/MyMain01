#include "MgrSpacetime.h"

#include "scene/MgrSpacetime/MgrWorld.h"
#include "util/MgrUtil.h"
#include "MgrCaretaker.h"
#include "jp/ggaf/core/scene/Scene.h"
#include "jp/ggaf/core/actor/SceneMediator.h"
#include "actor/camera/MgrCameraWorker.h"
#include "jp/ggaf/lib/util/VirtualButton.h"

using namespace GgafCore;
using namespace GgafDx;
using namespace GgafLib;
using namespace Mogera;

#define PRIMARY_VIEW 0
#define SECONDARY_VIEW 1

MgrSpacetime::MgrSpacetime(const char* prm_name, MgrCamera* prm_pCam) :
        GgafLib::DefaultSpacetime(prm_name, prm_pCam) {
    pWorld_ = nullptr;
    UTIL::left_top_x_ = CONFIG::DUAL_VIEW ? PX_C(P_CARETAKER->_aRect_HarfRenderTargetBuffer[PRIMARY_VIEW].left) :
                                            PX_C(P_CARETAKER->_rectRenderTargetBuffer.left);
    UTIL::left_top_y_ = CONFIG::DUAL_VIEW ? PX_C(P_CARETAKER->_aRect_HarfRenderTargetBuffer[PRIMARY_VIEW].top) :
                                            PX_C(P_CARETAKER->_rectRenderTargetBuffer.top);
    UTIL::center_x_ = PX_C(CONFIG::RENDER_TARGET_BUFFER_WIDTH / 2);
    UTIL::center_y_ = PX_C(CONFIG::RENDER_TARGET_BUFFER_HEIGHT / 2);

    pActiveCamWorker_ = NEW MgrCameraWorker("MgrCameraWorker", prm_pCam);
    bringSceneMediator()->appendGroupChild(pActiveCamWorker_); //���f�t�H���g�J�������[�N

    pVb_ = NEW VirtualButton();
    pVb_->remapK(VB_UI_DEBUG, VBK_Q     );
    pVb_->remapK(VB_PAUSE   , VBK_ESCAPE);
    pVb_->remap(VB_UP     , VBK_UP   , VBJ_Y_POS_MINUS);  //VB_UP      = �L�[�{�[�h�� �܂��́AY���| �Ƃ���B
    pVb_->remap(VB_DOWN   , VBK_DOWN , VBJ_Y_POS_PLUS );  //VB_DOWN    = �L�[�{�[�h�� �܂��́AY���{ �Ƃ���B
    pVb_->remap(VB_LEFT   , VBK_LEFT , VBJ_X_POS_MINUS);  //VB_LEFT    = �L�[�{�[�h�� �܂��́AX���| �Ƃ���B
    pVb_->remap(VB_RIGHT  , VBK_RIGHT, VBJ_X_POS_PLUS );  //VB_RIGHT   = �L�[�{�[�h�� �܂��́AX���{ �Ƃ���B
    pVb_->remap(VB_BUTTON1, VBK_SPACE, VBJ_BUTTON_01  );  //VB_BUTTON1 = �X�y�[�X�L�[ �܂��� �W���C�X�e�B�b�N�{�^���P �Ƃ���B
    _TRACE_("Spacetime Bound = X("<<_x_bound_left<<" ~ "<<_x_bound_right<<") Y("<<_y_bound_bottom<<" ~ "<<_y_bound_top<<") Z("<<_z_bound_near<<" ~ "<<_z_bound_far<<")");
}

void MgrSpacetime::initialize() {
    //���E�V�[���������A���V�[���̔z���ɏ���������
    pWorld_ = desireScene(Mogera::MgrWorld);
    appendChild(pWorld_);
}

void MgrSpacetime::processBehavior() {
    pVb_->update(); //���͏󋵍X�V

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

MgrSpacetime::~MgrSpacetime() {
    GGAF_DELETE(pVb_);
}

