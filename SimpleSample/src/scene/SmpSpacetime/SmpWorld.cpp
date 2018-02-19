#include "SmpWorld.h"

#include "actor/SmpActor.h"

using namespace SimpleSample;

SmpWorld::Mediator::Mediator(SmpWorld* prm_pSmpWorld) :
        GgafLib::DefaultSceneMediator(prm_pSmpWorld) {
    vb_.remap(VB_UP     , VBK_UP   , VBJ_Y_POS_MINUS);  //VB_UP      = �L�[�{�[�h�� �܂��́AY���| �Ƃ���B
    vb_.remap(VB_DOWN   , VBK_DOWN , VBJ_Y_POS_PLUS );  //VB_DOWN    = �L�[�{�[�h�� �܂��́AY���{ �Ƃ���B
    vb_.remap(VB_LEFT   , VBK_LEFT , VBJ_X_POS_MINUS);  //VB_LEFT    = �L�[�{�[�h�� �܂��́AX���| �Ƃ���B
    vb_.remap(VB_RIGHT  , VBK_RIGHT, VBJ_X_POS_PLUS );  //VB_RIGHT   = �L�[�{�[�h�� �܂��́AX���{ �Ƃ���B
    vb_.remap(VB_BUTTON1, VBK_SPACE, VBJ_BUTTON_01  );  //VB_BUTTON1 = �X�y�[�X�L�[ �܂��� �W���C�X�e�B�b�N�{�^���P �Ƃ���B
}


SmpWorld::SmpWorld(const char* prm_name) :
        GgafLib::DefaultScene(prm_name, NEW SmpWorld::Mediator(this)) {
    SmpActor* pActor = new SmpActor("TEST");  //�L�����N�^�[�쐬
    bringSceneMediator()->addSubGroup(pActor);  //�L�����N�^�[���V�[���ē̔z���ɏ����i�\�������j
}

void SmpWorld::initialize() {
}

void SmpWorld::processBehavior() {
}

SmpWorld::~SmpWorld() {
}
