#include "SmpSpacetime.h"

#include "jp/ggaf/lib/util/VirtualButton.h"
#include "SmpCaretaker.h"
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
    pVb_->remap(0, VB_UP     , VBK_UP   , VBJ_BASE_POV_UP   );  //VB_UP      = �L�[�{�[�h�� �܂��́A�n�b�g�X�C�b�`�� �Ƃ���B
    pVb_->remap(0, VB_DOWN   , VBK_DOWN , VBJ_BASE_POV_DOWN );  //VB_DOWN    = �L�[�{�[�h�� �܂��́A�n�b�g�X�C�b�`�� �Ƃ���B
    pVb_->remap(0, VB_LEFT   , VBK_LEFT , VBJ_BASE_POV_LEFT );  //VB_LEFT    = �L�[�{�[�h�� �܂��́A�n�b�g�X�C�b�`�� �Ƃ���B
    pVb_->remap(0, VB_RIGHT  , VBK_RIGHT, VBJ_BASE_POV_RIGHT);  //VB_RIGHT   = �L�[�{�[�h�� �܂��́A�n�b�g�X�C�b�`�E �Ƃ���B
    pVb_->remap(0, VB_BUTTON1, VBK_SPACE, VBJ_P1_BUTTON_01  );  //VB_BUTTON1 = �X�y�[�X�L�[ �܂��� �W���C�X�e�B�b�N�{�^���P �Ƃ���B
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

