#include "MgrSpacetime.h"

#include "scene/MgrSpacetime/MgrWorld.h"
#include "util/MgrUtil.h"
#include "MgrGod.h"
#include "jp/ggaf/core/scene/Scene.h"
#include "jp/ggaf/core/actor/SceneMediator.h"
#include "actor/camera/MgrCameraWorker.h"
#include "jp/ggaf/lib/util/VirtualButton.h"



using namespace GgafLib;
using namespace Mogera;

#define PRIMARY_VIEW 0
#define SECONDARY_VIEW 1

MgrSpacetime::MgrSpacetime(const char* prm_name, MgrCamera* prm_pCam) :
        GgafLib::DefaultSpacetime(prm_name, prm_pCam) {
    pWorld_ = nullptr;
    UTIL::left_top_x_ = CONFIG::DUAL_VIEW ? PX_C(P_GOD->_aRect_HarfRenderTargetBuffer[PRIMARY_VIEW].left) :
                                              PX_C(P_GOD->_rectRenderTargetBuffer.left);
    UTIL::left_top_y_ = CONFIG::DUAL_VIEW ? PX_C(P_GOD->_aRect_HarfRenderTargetBuffer[PRIMARY_VIEW].top) :
                                                      PX_C(P_GOD->_rectRenderTargetBuffer.top);
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


//    angle rz,ry;
//    UTIL::convVectorToRzRy(1.0,1.0,0.0,rz,ry);
//    _TRACE_("(rz,ry)=("<<rz<<","<<ry<<")");
//    UTIL::convVectorToRzRy(1.0,1.0,1.0,rz,ry);
//    _TRACE_("(rz,ry)=("<<rz<<","<<ry<<")");
//    UTIL::convVectorToRzRy(1.0,1.0,-1.0,rz,ry);
//    _TRACE_("(rz,ry)=("<<rz<<","<<ry<<")");
//    UTIL::convVectorToRzRy(1.0,-1.0,1.0,rz,ry);
//    _TRACE_("(rz,ry)=("<<rz<<","<<ry<<")");
//    UTIL::convVectorToRzRy(1.0,-1.0,-1.0,rz,ry);
//    _TRACE_("(rz,ry)=("<<rz<<","<<ry<<")");
//    UTIL::convVectorToRzRy(-1.0,1.0,1.0,rz,ry);
//    _TRACE_("(rz,ry)=("<<rz<<","<<ry<<")");
//    UTIL::convVectorToRzRy(-1.0,1.0,-1.0,rz,ry);
//    _TRACE_("(rz,ry)=("<<rz<<","<<ry<<")");
//    UTIL::convVectorToRzRy(-1.0,-1.0,1.0,rz,ry);
//    _TRACE_("(rz,ry)=("<<rz<<","<<ry<<")");
//    UTIL::convVectorToRzRy(-1.0,1.0,-1.0,rz,ry);
//    _TRACE_("(rz,ry)=("<<rz<<","<<ry<<")");
//    UTIL::convVectorToRzRy(-1.0,-1.0,-1.0,rz,ry);
//    _TRACE_("(rz,ry)=("<<rz<<","<<ry<<")");

}

void MgrSpacetime::processBehavior() {
    pVb_->update(); //���͏󋵍X�V
}

MgrSpacetime::~MgrSpacetime() {
    GGAF_DELETE(pVb_);
}

