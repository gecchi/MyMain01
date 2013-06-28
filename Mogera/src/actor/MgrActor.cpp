#include "stdafx.h"
#include "actor/MgrActor.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"

using namespace Mogera;

MgrActor::MgrActor(const char* prm_name) :
        GgafLib::DefaultMeshActor(prm_name, "Guruguru") { //Guruguru.x ���Q�Ƃ����B
}

void MgrActor::initialize() {
    //���W�ݒ�
    position(0, 0, 0); //(0,0,0) �͉�ʂ̒��S
    //����A�ɃL������Z����]�̊p���x��ݒ�(���t���[��2�x)
    _pKurokoA->setFaceAngVelo(AXIS_Z, D_ANG(2));
}

void MgrActor::processBehavior() {
    _pKurokoA->behave(); //����A������������iZ����]����j
}

MgrActor::~MgrActor() {
}
