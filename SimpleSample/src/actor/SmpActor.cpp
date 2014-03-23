#include "stdafx.h"
#include "SmpActor.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"

using namespace SimpleSample;

SmpActor::SmpActor(const char* prm_name) :
        GgafLib::DefaultMeshActor(prm_name, "Guruguru") { //Guruguru.x ���Q�Ƃ����B
}

void SmpActor::initialize() {
    //���W�ݒ�
    position(0, 0, 0); //(0,0,0) �͉�ʂ̒��S
    //���߂ɃL������Z����]�̊p���x��ݒ�(���t���[��2�x)
    getKuroko()->setFaceAngVelo(AXIS_Z, D_ANG(2));
}

void SmpActor::processBehavior() {
    getKuroko()->behave(); //���߂�����������iZ����]����j
}

SmpActor::~SmpActor() {
}
