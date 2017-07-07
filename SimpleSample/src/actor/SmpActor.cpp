#include "SmpActor.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoFaceAngAssistant.h"

using namespace SimpleSample;

SmpActor::SmpActor(const char* prm_name) :
        GgafLib::DefaultMeshActor(prm_name, "Guruguru") { //Guruguru.x ���Q�Ƃ����B
}

void SmpActor::initialize() {
    //���W�ݒ�
    setPosition(0, 0, 0);
    //���߂ɃL������Z����]�̊p���x��ݒ�(���t���[��2�x)
    getKuroko()->setFaceAngVelo(AXIS_Z, D_ANG(2));
    getKuroko()->asstFaceAng()->twist(AXIS_Y, D_ANG(180), D_ANG(0), -1,
                                      TURN_COUNTERCLOCKWISE, 30,
                                      0.49, 0.51, 0,
                                      true);
}

void SmpActor::processBehavior() {
    getKuroko()->behave(); //���߂�����������iZ����]����j
}

SmpActor::~SmpActor() {
}
