#include "SmpActor.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoFaceAngAssistant.h"
#include "jp/ggaf/lib/util/VirtualButton.h"
#include "scene/SmpSpacetime/SmpWorld.h"

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
    //�L�������{�^�����͂ňړ�
    GgafLib::VirtualButton* vb = ((SmpWorld::Mediator*)getMySceneMediator())->getVB();
    if (vb->isPressed(VB_BUTTON1)) {
        //�{�^���P�i�X�y�[�X�L�[�j�������Ȃ���̏ꍇ
        if (vb->isPressed(VB_UP)) {
            _z += PX_C(2); //��
        }
        if (vb->isPressed(VB_DOWN)) {
            _z -= PX_C(2); //��O
        }
    } else {
        //�{�^���P�i�X�y�[�X�L�[�j�𗣂��Ă���ꍇ
        if (vb->isPressed(VB_RIGHT)) {
            _x += PX_C(2); //�E
        }
        if (vb->isPressed(VB_LEFT)) {
            _x -= PX_C(2); //��
        }
        if (vb->isPressed(VB_UP)) {
            _y += PX_C(2); //��
        }
        if (vb->isPressed(VB_DOWN)) {
            _y -= PX_C(2); //��
        }
    }
    getKuroko()->behave(); //���߂�����������iZ����]����j
}

SmpActor::~SmpActor() {
}
