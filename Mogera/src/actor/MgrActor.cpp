#include "stdafx.h"
using namespace Mogera;

MgrActor::MgrActor(const char* prm_name) :
        GgafLib::DefaultMeshActor(prm_name, "Guruguru") { //Guruguru.x ���Q�Ƃ����B
}

void MgrActor::initialize() {
    //���W�ݒ�
    locate(0, 0, 0); //(0,0,0) �͉�ʂ̒��S
    //���qA�ɃL������Z����]�̊p���x��ݒ�(���t���[��2�x)
    _pKurokoA->setFaceAngVelo(AXIS_Z, D_ANG(2));
}

void MgrActor::processBehavior() {
    _pKurokoA->behave(); //���qA������������iZ����]����j
}

MgrActor::~MgrActor() {
}
