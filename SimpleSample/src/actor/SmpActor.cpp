#include "SmpActor.h"

#include "jp/ggaf/dx/actor/supporter/LocoVehicle.h"
#include "jp/ggaf/lib/util/VirtualButton.h"
#include "SmpCaretaker.h"
#include "scene/SmpSpacetime.h"

using namespace SimpleSample;

SmpActor::SmpActor(const char* prm_name) :
    GgafLib::DefaultMeshActor(prm_name, "Guruguru") { //Guruguru.x ���Q�Ƃ����B
}

void SmpActor::initialize() {
    //���W�ݒ�
    setPosition(0, 0, 0);
    //�ړ��ԗ��ɃL������Z����]�̊p���x��ݒ�(���t���[��2�x)
    GgafDx::LocoVehicle* pLocoVehicle = getLocoVehicle();
    pLocoVehicle->setFaceAngVelo(AXIS_Z, D_ANG(2));
}

void SmpActor::processBehavior() {
    //�L�������{�^�����͂ňړ�
    static GgafLib::VirtualButton* pVb = ((SmpSpacetime*)pCARETAKER->getSpacetime())->getVB();
    static const coord d = PX_C(2);
    if (pVb->isPressed(0, VB_BUTTON1)) {
        //�{�^���P�i�X�y�[�X�L�[�j�������Ȃ���̏ꍇ
        if (pVb->isPressed(0, VB_UP)) {
            _z += d; //���ړ�
        }
        if (pVb->isPressed(0, VB_DOWN)) {
            _z -= d; //��O�ړ�
        }
    } else {
        //�{�^���P�i�X�y�[�X�L�[�j�𗣂��Ă���ꍇ
        if (pVb->isPressed(0, VB_RIGHT)) {
            _x += d; //�E�ړ�
        }
        if (pVb->isPressed(0, VB_LEFT)) {
            _x -= d; //���ړ�
        }
        if (pVb->isPressed(0, VB_UP)) {
            _y += d; //��ړ�
        }
        if (pVb->isPressed(0, VB_DOWN)) {
            _y -= d; //���ړ�
        }
    }
    getLocoVehicle()->behave(); //�ړ��ԗ�������������iZ����]����j
}

SmpActor::~SmpActor() {
}
