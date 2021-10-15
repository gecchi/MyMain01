#include "SmpActor.h"

#include "jp/ggaf/dx/actor/supporter/VecDriver.h"
#include "jp/ggaf/lib/util/VirtualButton.h"
#include "SmpGod.h"
#include "scene/SmpSpacetime.h"

using GgafLib::DefaultMeshActor;
using GgafLib::VirtualButton;
using GgafDx::VecDriver;
using namespace SimpleSample;

SmpActor::SmpActor(const char* prm_name) :
        DefaultMeshActor(prm_name, "Guruguru") { //Guruguru.x ���Q�Ƃ����B
}

void SmpActor::initialize() {
    //���W�ݒ�
    setPosition(0, 0, 0);

    //�͎ԂɃL������Z����]�̊p���x��ݒ�(���t���[��2�x)
    VecDriver* pVecDriver = getVecDriver();
    pVecDriver->setFaceAngVelo(AXIS_Z, D_ANG(2));
}

void SmpActor::processBehavior() {
    //�L�������{�^�����͂ňړ�
    static VirtualButton* pVb = ((SmpSpacetime*)pGOD->getSpacetime())->getVB();
    static const coord d = PX_C(2);
    if (pVb->isPressed(VB_BUTTON1)) {
        //�{�^���P�i�X�y�[�X�L�[�j�������Ȃ���̏ꍇ
        if (pVb->isPressed(VB_UP)) {
            _z += d; //��
        }
        if (pVb->isPressed(VB_DOWN)) {
            _z -= d; //��O
        }
    } else {
        //�{�^���P�i�X�y�[�X�L�[�j�𗣂��Ă���ꍇ
        if (pVb->isPressed(VB_RIGHT)) {
            _x += d; //�E
        }
        if (pVb->isPressed(VB_LEFT)) {
            _x -= d; //��
        }
        if (pVb->isPressed(VB_UP)) {
            _y += d; //��
        }
        if (pVb->isPressed(VB_DOWN)) {
            _y -= d; //��
        }
    }
    getVecDriver()->behave(); //�͎Ԃ�����������iZ����]����j
}

SmpActor::~SmpActor() {
}
