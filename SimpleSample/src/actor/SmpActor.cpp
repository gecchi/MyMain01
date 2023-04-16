#include "SmpActor.h"

#include "jp/ggaf/dx/actor/supporter/VecVehicle.h"
#include "jp/ggaf/lib/util/VirtualButton.h"
#include "SmpCaretaker.h"
#include "scene/SmpSpacetime.h"

using GgafLib::DefaultMeshActor;
using GgafLib::VirtualButton;
using GgafDx::VecVehicle;
using namespace SimpleSample;

SmpActor::SmpActor(const char* prm_name) :
        DefaultMeshActor(prm_name, "Guruguru") { //Guruguru.x ���Q�Ƃ����B
}

void SmpActor::initialize() {
    //���W�ݒ�
    setPosition(0, 0, 0);

    //�͎ԂɃL������Z����]�̊p���x��ݒ�(���t���[��2�x)
    VecVehicle* pVecVehicle = getVecVehicle();
    pVecVehicle->setFaceAngVelo(AXIS_Z, D_ANG(2));
}

void SmpActor::processBehavior() {
    //�L�������{�^�����͂ňړ�
    static VirtualButton* pVb = ((SmpSpacetime*)pCARETAKER->getSpacetime())->getVB();
    static const coord d = PX_C(2);
    if (pVb->isPressed(0, VB_BUTTON1)) {
        //�{�^���P�i�X�y�[�X�L�[�j�������Ȃ���̏ꍇ
        if (pVb->isPressed(0, VB_UP)) {
            _z += d; //��
        }
        if (pVb->isPressed(0, VB_DOWN)) {
            _z -= d; //��O
        }
    } else {
        //�{�^���P�i�X�y�[�X�L�[�j�𗣂��Ă���ꍇ
        if (pVb->isPressed(0, VB_RIGHT)) {
            _x += d; //�E
        }
        if (pVb->isPressed(0, VB_LEFT)) {
            _x -= d; //��
        }
        if (pVb->isPressed(0, VB_UP)) {
            _y += d; //��
        }
        if (pVb->isPressed(0, VB_DOWN)) {
            _y -= d; //��
        }
    }
    getVecVehicle()->behave(); //�͎Ԃ�����������iZ����]����j
}

SmpActor::~SmpActor() {
}
