#include "stdafx.h"
using namespace SimpleSample;

SmpWorld::SmpWorld(const char* prm_name) : GgafLib::DefaultScene(prm_name) {
    pActor_ = new SmpActor("TEST");     //�L�����쐬���ێ�
    getDirector()->addSubGroup(pActor_); //�L�������V�[���ē̔z���ɏ����i�\�������j
    GgafLib::VirtualButton::_tagKeymap.BUTTON1 = DIK_SPACE; //�{�^���P=�X�y�[�X�L�[ �Ƃ���B
}

void SmpWorld::processBehavior() {
    //�L�������{�^�����͂ňړ�
    vb_.update(); //���͏󋵍X�V
    if (vb_.isBeingPressed(VB_BUTTON1)) {
        //�{�^���P�i�X�y�[�X�L�[�j�������Ȃ���̏ꍇ
        if (vb_.isBeingPressed(VB_UP)) {
            pActor_->_Z += PX2CO(2); //��
        }
        if (vb_.isBeingPressed(VB_DOWN)) {
            pActor_->_Z -= PX2CO(2); //��O
        }
    } else {
        //�{�^���P�i�X�y�[�X�L�[�j�𗣂��Ă���ꍇ
        if (vb_.isBeingPressed(VB_RIGHT)) {
            pActor_->_X += PX2CO(2); //�E
        }
        if (vb_.isBeingPressed(VB_LEFT)) {
            pActor_->_X -= PX2CO(2); //��
        }
        if (vb_.isBeingPressed(VB_UP)) {
            pActor_->_Y += PX2CO(2); //��
        }
        if (vb_.isBeingPressed(VB_DOWN)) {
            pActor_->_Y -= PX2CO(2); //��
        }
    }
}

SmpWorld::~SmpWorld() {
}
