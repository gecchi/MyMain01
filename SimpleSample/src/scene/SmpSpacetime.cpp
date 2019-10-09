#include "SmpSpacetime.h"

#include "jp/ggaf/lib/util/VirtualButton.h"
#include "SmpGod.h"
#include "actor/SmpCamera.h"
#include "SmpSpacetime/SmpWorld.h"

using GgafLib::VirtualButton;
using namespace SimpleSample;

SmpSpacetime::SmpSpacetime(const char* prm_name, SmpCamera* prm_pCam) :
        GgafLib::DefaultSpacetime(prm_name, prm_pCam) {
    //SmpWorld�V�[���̍쐬�v��
    requestScene(0, SmpWorld);
    //���̐�(Spacetime)�R���X�g���N�^���ŁA
    //���̃V�[���̏���( appendChild(GgafCore::Scene*) )�͎��s���Ȃ��ł��������B

    pVb_ = new VirtualButton(); //���z�{�^���̐���
    pVb_->remap(VB_UP     , VBK_UP   , VBJ_Y_POS_MINUS);  //VB_UP      = �L�[�{�[�h�� �܂��́AY���| �Ƃ���B
    pVb_->remap(VB_DOWN   , VBK_DOWN , VBJ_Y_POS_PLUS );  //VB_DOWN    = �L�[�{�[�h�� �܂��́AY���{ �Ƃ���B
    pVb_->remap(VB_LEFT   , VBK_LEFT , VBJ_X_POS_MINUS);  //VB_LEFT    = �L�[�{�[�h�� �܂��́AX���| �Ƃ���B
    pVb_->remap(VB_RIGHT  , VBK_RIGHT, VBJ_X_POS_PLUS );  //VB_RIGHT   = �L�[�{�[�h�� �܂��́AX���{ �Ƃ���B
    pVb_->remap(VB_BUTTON1, VBK_SPACE, VBJ_BUTTON_01  );  //VB_BUTTON1 = �X�y�[�X�L�[ �܂��� �W���C�X�e�B�b�N�{�^���P �Ƃ���B
}

void SmpSpacetime::initialize() {
    //���E�V�[��(SmpWorld)��z���ɏ���������
    appendChild(receiveScene(0));
}

void SmpSpacetime::processBehavior() {
    //���z�{�^���̏�Ԃ��X�V
    pVb_->update();
}

SmpSpacetime::~SmpSpacetime() {
    delete pVb_;
}

