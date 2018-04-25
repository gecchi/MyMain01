#include "SmpSpacetime.h"

#include "SmpSpacetime/SmpWorld.h"
#include "actor/SmpCamera.h"

using namespace SimpleSample;

SmpSpacetime::SmpSpacetime(const char* prm_name, SmpCamera* prm_pCam) :
        GgafLib::DefaultSpacetime(prm_name, prm_pCam) {
    //SmpWorld�V�[���̍쐬����肩������
    wantScene(0, SimpleSample::SmpWorld, "SMP_WORLD");
    //���̐�(Spacetime)�R���X�g���N�^���ŁA
    //���̃V�[���̏���( addSubLast(GgafScene*) )�͎��s���Ȃ��ł��������B

    vb_.remap(VB_UP     , VBK_UP   , VBJ_Y_POS_MINUS);  //VB_UP      = �L�[�{�[�h�� �܂��́AY���| �Ƃ���B
    vb_.remap(VB_DOWN   , VBK_DOWN , VBJ_Y_POS_PLUS );  //VB_DOWN    = �L�[�{�[�h�� �܂��́AY���{ �Ƃ���B
    vb_.remap(VB_LEFT   , VBK_LEFT , VBJ_X_POS_MINUS);  //VB_LEFT    = �L�[�{�[�h�� �܂��́AX���| �Ƃ���B
    vb_.remap(VB_RIGHT  , VBK_RIGHT, VBJ_X_POS_PLUS );  //VB_RIGHT   = �L�[�{�[�h�� �܂��́AX���{ �Ƃ���B
    vb_.remap(VB_BUTTON1, VBK_SPACE, VBJ_BUTTON_01  );  //VB_BUTTON1 = �X�y�[�X�L�[ �܂��� �W���C�X�e�B�b�N�{�^���P �Ƃ���B
}

void SmpSpacetime::initialize() {
    //���E�V�[��(SmpWorld)��z���ɏ���������
    addSubLast(grantScene(0));
}

void SmpSpacetime::processBehavior() {
    vb_.update();
}

SmpSpacetime::~SmpSpacetime() {
}

