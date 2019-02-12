#include "SmpGod.h"

#include "actor/SmpCamera.h"
#include "scene/SmpSpacetime.h"

using namespace SimpleSample;

SmpGod::SmpGod() : GgafLib::DefaultGod() {
    vb_.remap(VB_UP     , VBK_UP   , VBJ_Y_POS_MINUS);  //VB_UP      = �L�[�{�[�h�� �܂��́AY���| �Ƃ���B
    vb_.remap(VB_DOWN   , VBK_DOWN , VBJ_Y_POS_PLUS );  //VB_DOWN    = �L�[�{�[�h�� �܂��́AY���{ �Ƃ���B
    vb_.remap(VB_LEFT   , VBK_LEFT , VBJ_X_POS_MINUS);  //VB_LEFT    = �L�[�{�[�h�� �܂��́AX���| �Ƃ���B
    vb_.remap(VB_RIGHT  , VBK_RIGHT, VBJ_X_POS_PLUS );  //VB_RIGHT   = �L�[�{�[�h�� �܂��́AX���{ �Ƃ���B
    vb_.remap(VB_BUTTON1, VBK_SPACE, VBJ_BUTTON_01  );  //VB_BUTTON1 = �X�y�[�X�L�[ �܂��� �W���C�X�e�B�b�N�{�^���P �Ƃ���B
}

GgafCore::Spacetime* SmpGod::createSpacetime() {
    //�u���̐��v�̍쐬�������I�[�o�[���C�h���A�������Ă��������B
    SmpCamera* pCam = new SmpCamera("SMP_CAM"); //�J�����쐬���A
    SmpSpacetime* pSpacetime = new SmpSpacetime("SMP_SPACETIME", pCam); //�J�����������Ɂu���̐��v�𐶐����A
    return pSpacetime; //���������u���̐��v��Ԓl�Ƃ��܂��B
}

SmpGod::~SmpGod() {
}

