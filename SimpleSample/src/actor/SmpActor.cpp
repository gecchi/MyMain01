#include "SmpActor.h"

#include "jp/ggaf/dx/actor/supporter/Kuroko.h"
#include "jp/ggaf/lib/util/VirtualButton.h"
#include "SmpGod.h"
#include "scene/SmpSpacetime.h"

using GgafLib::DefaultMeshActor;
using GgafLib::VirtualButton;
using GgafDx::Kuroko;
using namespace SimpleSample;

SmpActor::SmpActor(const char* prm_name) :
        DefaultMeshActor(prm_name, "Guruguru") { //Guruguru.x ���Q�Ƃ����B
}

void SmpActor::initialize() {
    //���W�ݒ�
    setPosition(0, 0, 0);

    //���߂ɃL������Z����]�̊p���x��ݒ�(���t���[��2�x)
    Kuroko* kuroko = getKuroko();
    kuroko->setFaceAngVelo(AXIS_Z, D_ANG(2));
}

void SmpActor::processBehavior() {
    //�L�������{�^�����͂ňړ�
    VirtualButton* vb = pGOD->getVB();
    static const coord d = PX_C(2);
    if (vb->isPressed(VB_BUTTON1)) {
        //�{�^���P�i�X�y�[�X�L�[�j�������Ȃ���̏ꍇ
        if (vb->isPressed(VB_UP)) {
            _z += d; //��
        }
        if (vb->isPressed(VB_DOWN)) {
            _z -= d; //��O
        }
    } else {
        //�{�^���P�i�X�y�[�X�L�[�j�𗣂��Ă���ꍇ
        if (vb->isPressed(VB_RIGHT)) {
            _x += d; //�E
        }
        if (vb->isPressed(VB_LEFT)) {
            _x -= d; //��
        }
        if (vb->isPressed(VB_UP)) {
            _y += d; //��
        }
        if (vb->isPressed(VB_DOWN)) {
            _y -= d; //��
        }
    }
    getKuroko()->behave(); //���߂�����������iZ����]����j
}

SmpActor::~SmpActor() {
}
