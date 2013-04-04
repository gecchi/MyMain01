#include "stdafx.h"
using namespace SimpleSample;

SmpActor::SmpActor(const char* prm_name) :
        GgafLib::DefaultMeshActor(prm_name, "Guruguru") { //Guruguru.x ���Q�Ƃ����B
}

void SmpActor::initialize() {
    //���W�ݒ�
    locate(0, 0, 0); //(0,0,0) �͉�ʂ̒��S
    //����A�ɃL������Z����]�̊p���x��ݒ�(���t���[��2�x)
    _pKurokoA->setFaceAngVelo(AXIS_Z, D_ANG(2));
}

void SmpActor::processBehavior() {
    _pKurokoA->behave(); //����A������������iZ����]����j
}

SmpActor::~SmpActor() {
}
