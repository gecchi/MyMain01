#include "stdafx.h"
using namespace GgafLib;
using namespace VVViewer;

VvvActor::VvvActor(const char* prm_name) :
        GgafLib::DefaultMeshActor(prm_name, "Guruguru") { //Guruguru.x ���Q�Ƃ����B
}

void VvvActor::initialize() {
    //���W�ݒ�
    _X = _Y = _Z = 0; //(0,0,0) �͉�ʂ̒��S
}

void VvvActor::processBehavior() {
    //�L�������{�^�����͂ňړ�
    VirtualButton* vb = P_WORLD->vb_;
    if (vb->isBeingPressed(VB_BUTTON1)) {
        //�{�^���P�i�X�y�[�X�L�[�j�������Ȃ���̏ꍇ
        if (vb->isBeingPressed(VB_UP)) {
            _Z += PX_C(2); //��
        }
        if (vb->isBeingPressed(VB_DOWN)) {
            _Z -= PX_C(2); //��O
        }
    } else {
        //�{�^���P�i�X�y�[�X�L�[�j�𗣂��Ă���ꍇ
        if (vb->isBeingPressed(VB_RIGHT)) {
            _X += PX_C(2); //�E
        }
        if (vb->isBeingPressed(VB_LEFT)) {
            _X -= PX_C(2); //��
        }
        if (vb->isBeingPressed(VB_UP)) {
            _Y += PX_C(2); //��
        }
        if (vb->isBeingPressed(VB_DOWN)) {
            _Y -= PX_C(2); //��
        }
    }
}

VvvActor::~VvvActor() {
}
