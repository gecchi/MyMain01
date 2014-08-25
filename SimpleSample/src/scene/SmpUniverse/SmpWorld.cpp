#include "SmpWorld.h"

#include "jp/ggaf/core/actor/GgafSceneDirector.h"
#include "actor/SmpActor.h"

using namespace SimpleSample;

SmpWorld::SmpWorld(const char* prm_name) : GgafLib::DefaultScene(prm_name) {
    pActor_ = new SmpActor("TEST");  //�L�����쐬���ێ�
    getSceneDirector()->addSubGroup(pActor_);  //�L�������V�[���ē̔z���ɏ����i�\�������j
    GgafLib::VirtualButton::_keyboardmap.BUTTON1 = DIK_SPACE;  //�{�^���P=�X�y�[�X�L�[ �Ƃ���B
}

void SmpWorld::initialize() {
}

void SmpWorld::processBehavior() {
    //�L�������{�^�����͂ňړ�
    vb_.update(); //���͏󋵍X�V
    if (vb_.isBeingPressed(VB_BUTTON1)) {
        //�{�^���P�i�X�y�[�X�L�[�j�������Ȃ���̏ꍇ
        if (vb_.isBeingPressed(VB_UP)) {
            pActor_->_z += PX_C(2); //��
        }
        if (vb_.isBeingPressed(VB_DOWN)) {
            pActor_->_z -= PX_C(2); //��O
        }
    } else {
        //�{�^���P�i�X�y�[�X�L�[�j�𗣂��Ă���ꍇ
        if (vb_.isBeingPressed(VB_RIGHT)) {
            pActor_->_x += PX_C(2); //�E
        }
        if (vb_.isBeingPressed(VB_LEFT)) {
            pActor_->_x -= PX_C(2); //��
        }
        if (vb_.isBeingPressed(VB_UP)) {
            pActor_->_y += PX_C(2); //��
        }
        if (vb_.isBeingPressed(VB_DOWN)) {
            pActor_->_y -= PX_C(2); //��
        }
    }
}

SmpWorld::~SmpWorld() {
}
