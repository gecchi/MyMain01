#include "SmpWorld.h"

#include "jp/ggaf/core/actor/GgafSceneMediator.h"
#include "actor/SmpActor.h"

using namespace SimpleSample;

SmpWorld::SmpWorld(const char* prm_name) : GgafLib::DefaultScene(prm_name) {
    pActor_ = new SmpActor("TEST");  //�L�����N�^�[�쐬���ێ�
    bringSceneMediator()->addSubGroup(pActor_);  //�L�����N�^�[���V�[������҂̔z���ɏ����i�\�������j
    vb_.remap(VB_UP     , VBK_UP   , VBJ_Y_POS_MINUS);  //VB_UP      = �L�[�{�[�h�� �܂��́AY���| �Ƃ���B
    vb_.remap(VB_DOWN   , VBK_DOWN , VBJ_Y_POS_PLUS );  //VB_DOWN    = �L�[�{�[�h�� �܂��́AY���{ �Ƃ���B
    vb_.remap(VB_LEFT   , VBK_LEFT , VBJ_X_POS_MINUS);  //VB_LEFT    = �L�[�{�[�h�� �܂��́AX���| �Ƃ���B
    vb_.remap(VB_RIGHT  , VBK_RIGHT, VBJ_X_POS_PLUS );  //VB_RIGHT   = �L�[�{�[�h�� �܂��́AX���{ �Ƃ���B
    vb_.remap(VB_BUTTON1, VBK_SPACE, VBJ_BUTTON_01  );  //VB_BUTTON1 = �X�y�[�X�L�[ �܂��� �W���C�X�e�B�b�N�{�^���P �Ƃ���B
}

void SmpWorld::initialize() {
}

void SmpWorld::processBehavior() {
    //�L�������{�^�����͂ňړ�
    vb_.update(); //���͏󋵍X�V
    if (vb_.isPressed(VB_BUTTON1)) {
        //�{�^���P�i�X�y�[�X�L�[�j�������Ȃ���̏ꍇ
        if (vb_.isPressed(VB_UP)) {
            pActor_->_z += PX_C(2); //��
        }
        if (vb_.isPressed(VB_DOWN)) {
            pActor_->_z -= PX_C(2); //��O
        }
    } else {
        //�{�^���P�i�X�y�[�X�L�[�j�𗣂��Ă���ꍇ
        if (vb_.isPressed(VB_RIGHT)) {
            pActor_->_x += PX_C(2); //�E
        }
        if (vb_.isPressed(VB_LEFT)) {
            pActor_->_x -= PX_C(2); //��
        }
        if (vb_.isPressed(VB_UP)) {
            pActor_->_y += PX_C(2); //��
        }
        if (vb_.isPressed(VB_DOWN)) {
            pActor_->_y -= PX_C(2); //��
        }
    }
}

SmpWorld::~SmpWorld() {
}
