#include "stdafx.h"
using namespace SimpleSample;

SmpActor::SmpActor(const char* prm_name) :
        GgafLib::DefaultMeshActor(prm_name, "Guruguru") { //Guruguru.x ���Q�Ƃ����B
}

void SmpActor::initialize() {
    //���W�ݒ�
    _X = _Y = _Z = 0; //(0,0,0) �͉�ʂ̒��S
    //���qA�ɃL������Z����]�̊p���x��ݒ�(���t���[��2�x)
    _pKurokoA->setFaceAngVelo(AXIS_Z, DEG2ANG(2));
}

void SmpActor::processBehavior() {
    _pKurokoA->behave(); //���qA������������iZ����]����j
}

SmpActor::~SmpActor() {
}
